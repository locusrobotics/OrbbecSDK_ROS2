#include <rclcpp/rclcpp.hpp>
#include <functional>
#include <atomic>
#include <memory>
#include <chrono>

namespace orbbec_camera {

/**
 * @brief Monitors trigger failures and cycles the streams to recover
 */
class TriggerFailureMonitor {
 public:
  /**
   * @brief Callback type for stream activation/deactivation
   * @return true if operation succeeded, false otherwise
   */
  using StreamControlCallback = std::function<bool()>;

  /**
   * @brief Callback type to check if pipeline is running
   * @return true if pipeline is started, false otherwise
   */
  using PipelineStatusCallback = std::function<bool()>;

  /**
   * @brief Constructor
   * @param node ROS node for creating timer
   * @param logger Logger for diagnostic messages
   */
  TriggerFailureMonitor(rclcpp::Node* node,
                        const rclcpp::Logger& logger);

  /**
   * @brief Destructor - cleans up timer
   */
  ~TriggerFailureMonitor();

  /**
   * @brief Set callback for deactivating streams
   * @param callback Function to call to deactivate streams
   */
  void setDeactivateCallback(StreamControlCallback callback);

  /**
   * @brief Set callback for activating streams
   * @param callback Function to call to activate streams
   */
  void setActivateCallback(StreamControlCallback callback);

  /**
   * @brief Set callback to check pipeline status
   * @param callback Function to call to check if pipeline is running
   */
  void setPipelineStatusCallback(PipelineStatusCallback callback);

  /**
   * @brief Record a trigger failure
   * 
   * Increments the consecutive failure count. Recovery will be triggered
   * by the monitor timer when threshold is exceeded.
   */
  void recordFailure();

  /**
   * @brief Record a successful trigger
   * 
   * Resets the consecutive failure count to zero.
   */
  void recordSuccess();

  /**
   * @brief Cleanup and stop monitoring
   */
  void cleanup();

 private:
  /**
   * @brief Timer callback to check for failures and trigger recovery
   */
  void timerCallback();

  /**
   * @brief Perform stream recovery (deactivate, wait, activate)
   * @return true if recovery succeeded, false otherwise
   */
  bool cycleStreams();

  rclcpp::Node* node_;                              
  rclcpp::Logger logger_;                           
  
  rclcpp::TimerBase::SharedPtr timer_;              
  int consecutive_failures_{0};    
  
  StreamControlCallback deactivate_callback_;       
  StreamControlCallback activate_callback_;         
  PipelineStatusCallback pipeline_status_callback_; 
  int failures_before_recovery_{2};
  double timer_period_seconds_{1.0}; 
};

}  // namespace orbbec_camera
