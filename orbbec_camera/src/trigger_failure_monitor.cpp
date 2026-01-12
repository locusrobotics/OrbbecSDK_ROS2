#include "orbbec_camera/trigger_failure_monitor.h"
#include <thread>

namespace orbbec_camera {

TriggerFailureMonitor::TriggerFailureMonitor(rclcpp::Node* node,
                                             const rclcpp::Logger& logger,
                                             int failures_before_recovery,
                                             double timer_period_seconds)
    : node_(node), logger_(logger), failures_before_recovery_(failures_before_recovery),
      timer_period_seconds_(timer_period_seconds) {

  RCLCPP_INFO_STREAM(logger_, "Setting up trigger failure monitor with period "
                                  << timer_period_seconds_ << " seconds, "
                                  << "failures_before_recovery: "
                                  << failures_before_recovery_);
  
  timer_ = node_->create_wall_timer(
      std::chrono::duration<double>(timer_period_seconds_),
      std::bind(&TriggerFailureMonitor::timerCallback, this));
}

TriggerFailureMonitor::~TriggerFailureMonitor() {
  cleanup();
}

void TriggerFailureMonitor::setDeactivateCallback(StreamControlCallback callback) {
  deactivate_callback_ = callback;
}

void TriggerFailureMonitor::setActivateCallback(StreamControlCallback callback) {
  activate_callback_ = callback;
}

void TriggerFailureMonitor::setPipelineStatusCallback(PipelineStatusCallback callback) {
  pipeline_status_callback_ = callback;
}

void TriggerFailureMonitor::recordFailure() {
  consecutive_failures_++;
}

void TriggerFailureMonitor::recordSuccess() {
  consecutive_failures_ = 0;
}

void TriggerFailureMonitor::cleanup() {
  if (timer_) {
    timer_->cancel();
    timer_.reset();
  }
}

void TriggerFailureMonitor::timerCallback() {
  // Check if pipeline is running
  if (pipeline_status_callback_ && !pipeline_status_callback_()) {
    return;
  }

  if (consecutive_failures_ >= failures_before_recovery_) {
    RCLCPP_WARN_STREAM(logger_, "Maximum consecutive trigger failures reached ("
                                    << consecutive_failures_ << "), attempting recovery...");
    
    if (cycleStreams()) {
      RCLCPP_INFO(logger_, "Stream recovery completed successfully");
      consecutive_failures_ = 0;
    } else {
      RCLCPP_ERROR(logger_, "Stream recovery failed");
    }
  }
}

bool TriggerFailureMonitor::cycleStreams() {
  // Deactivate streams
  if (!deactivate_callback_) {
    RCLCPP_ERROR(logger_, "Deactivate callback not set, cannot perform recovery");
    return false;
  }

  if (!deactivate_callback_()) {
    RCLCPP_ERROR(logger_, "Failed to deactivate streams during trigger failure recovery");
    return false;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(250));

  // Reactivate streams
  if (!activate_callback_) {
    RCLCPP_ERROR(logger_, "Activate callback not set, cannot complete recovery");
    return false;
  }

  if (!activate_callback_()) {
    RCLCPP_ERROR(logger_, "Failed to reactivate streams during trigger failure recovery");
    return false;
  }

  return true;
}

}  // namespace orbbec_camera
