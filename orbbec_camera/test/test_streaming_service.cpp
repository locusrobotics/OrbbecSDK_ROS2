/*******************************************************************************
 * Tests for the on-demand streaming service added in this PR.
 *
 * OBCameraNode cannot be instantiated without real hardware, so these tests
 * exercise the streaming state-machine logic through a minimal test fixture
 * that mirrors the member variables and methods involved in streaming.
 ******************************************************************************/

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>
#include <atomic>
#include <chrono>

using SetBool = std_srvs::srv::SetBool;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::HasSubstr;
using ::testing::IsFalse;
using ::testing::IsTrue;

/// Mock for the device trigger interface – replaces device_->triggerCapture().
class MockDevice {
 public:
  MOCK_METHOD(void, triggerCapture, ());
};

/// Minimal fixture that replicates the streaming state-machine from OBCameraNode
/// so we can unit-test the logic without needing a real Orbbec device.
class StreamingLogicTest : public ::testing::Test {
 protected:
  void SetUp() override {
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>("test_streaming_node");
    mock_device_ = std::make_shared<MockDevice>();
  }

  void TearDown() override { rclcpp::shutdown(); }

  // ---- mirrors of OBCameraNode members ----
  bool service_trigger_enabled_ = false;
  std::atomic_bool streaming_enabled_{false};
  double streaming_framerate_hz_ = 6.0;
  rclcpp::TimerBase::SharedPtr streaming_timer_;

  // ---- mirrors of OBCameraNode methods ----
  void setStreamingCallback(const std::shared_ptr<SetBool::Request>& request,
                            std::shared_ptr<SetBool::Response>& response) {
    if (!service_trigger_enabled_) {
      response->success = false;
      response->message = "Streaming requires service_trigger_enabled to be true";
      return;
    }
    if (request->data) {
      startStreaming();
    } else {
      stopStreaming();
    }
    response->success = true;
    response->message = streaming_enabled_ ? "Streaming started" : "Streaming stopped";
  }

  void startStreaming() {
    if (streaming_enabled_) {
      return;
    }
    streaming_enabled_ = true;
    streaming_timer_->reset();
  }

  void stopStreaming() {
    if (!streaming_enabled_) {
      return;
    }
    streaming_enabled_ = false;
    streaming_timer_->cancel();
  }

  void streamingTimerCallback() {
    if (!streaming_enabled_ || !service_trigger_enabled_) {
      return;
    }
    mock_device_->triggerCapture();
  }

  void createTimer() {
    streaming_timer_ = node_->create_wall_timer(
        std::chrono::milliseconds(static_cast<int>(1000.0 / streaming_framerate_hz_)),
        [this]() { streamingTimerCallback(); });
    streaming_timer_->cancel();
  }

  std::shared_ptr<SetBool::Response> callService(bool data) {
    auto request = std::make_shared<SetBool::Request>();
    request->data = data;
    auto response = std::make_shared<SetBool::Response>();
    setStreamingCallback(request, response);
    return response;
  }

  rclcpp::Node::SharedPtr node_;
  std::shared_ptr<MockDevice> mock_device_;
};

// ---------- Timer period calculation ----------

TEST_F(StreamingLogicTest, DefaultFramerateYields166msPeriod) {
  EXPECT_THAT(static_cast<int>(1000.0 / streaming_framerate_hz_), Eq(166));
}

TEST_F(StreamingLogicTest, ThirtyHzYields33msPeriod) {
  streaming_framerate_hz_ = 30.0;
  EXPECT_THAT(static_cast<int>(1000.0 / streaming_framerate_hz_), Eq(33));
}

TEST_F(StreamingLogicTest, OneHzYields1000msPeriod) {
  streaming_framerate_hz_ = 1.0;
  EXPECT_THAT(static_cast<int>(1000.0 / streaming_framerate_hz_), Eq(1000));
}

// ---------- Service rejects when service_trigger_enabled is false ----------

TEST_F(StreamingLogicTest, RejectsStartWhenServiceTriggerDisabled) {
  createTimer();
  service_trigger_enabled_ = false;

  auto response = callService(true);

  EXPECT_THAT(response->success, IsFalse());
  EXPECT_THAT(streaming_enabled_.load(), IsFalse());
  EXPECT_THAT(response->message, HasSubstr("service_trigger_enabled"));
}

TEST_F(StreamingLogicTest, RejectsStopWhenServiceTriggerDisabled) {
  createTimer();
  service_trigger_enabled_ = false;

  auto response = callService(false);

  EXPECT_THAT(response->success, IsFalse());
  EXPECT_THAT(response->message, HasSubstr("service_trigger_enabled"));
}

// ---------- Service accepts when service_trigger_enabled is true ----------

TEST_F(StreamingLogicTest, AcceptsStartWhenServiceTriggerEnabled) {
  createTimer();
  service_trigger_enabled_ = true;

  auto response = callService(true);

  EXPECT_THAT(response->success, IsTrue());
  EXPECT_THAT(streaming_enabled_.load(), IsTrue());
  EXPECT_THAT(response->message, Eq("Streaming started"));
}

TEST_F(StreamingLogicTest, AcceptsStopWhenServiceTriggerEnabled) {
  createTimer();
  service_trigger_enabled_ = true;

  callService(true);
  auto response = callService(false);

  EXPECT_THAT(response->success, IsTrue());
  EXPECT_THAT(streaming_enabled_.load(), IsFalse());
  EXPECT_THAT(response->message, Eq("Streaming stopped"));
}

// ---------- Idempotency ----------

TEST_F(StreamingLogicTest, StartIsIdempotent) {
  createTimer();
  service_trigger_enabled_ = true;

  startStreaming();
  EXPECT_THAT(streaming_enabled_.load(), IsTrue());

  startStreaming();
  EXPECT_THAT(streaming_enabled_.load(), IsTrue());
}

TEST_F(StreamingLogicTest, StopIsIdempotentWhenAlreadyStopped) {
  createTimer();

  stopStreaming();
  EXPECT_THAT(streaming_enabled_.load(), IsFalse());
}

TEST_F(StreamingLogicTest, StopIsIdempotentAfterStartStop) {
  createTimer();
  service_trigger_enabled_ = true;

  startStreaming();
  stopStreaming();
  stopStreaming();
  EXPECT_THAT(streaming_enabled_.load(), IsFalse());
}

// ---------- Timer callback guards ----------

TEST_F(StreamingLogicTest, TimerCallbackDoesNotTriggerWhenStreamingDisabled) {
  createTimer();
  service_trigger_enabled_ = true;
  streaming_enabled_ = false;

  EXPECT_CALL(*mock_device_, triggerCapture()).Times(0);
  streamingTimerCallback();
}

TEST_F(StreamingLogicTest, TimerCallbackDoesNotTriggerWhenServiceTriggerDisabled) {
  createTimer();
  service_trigger_enabled_ = false;
  streaming_enabled_ = true;

  EXPECT_CALL(*mock_device_, triggerCapture()).Times(0);
  streamingTimerCallback();
}

TEST_F(StreamingLogicTest, TimerCallbackTriggersWhenBothEnabled) {
  createTimer();
  service_trigger_enabled_ = true;
  streaming_enabled_ = true;

  EXPECT_CALL(*mock_device_, triggerCapture()).Times(1);
  streamingTimerCallback();
}

TEST_F(StreamingLogicTest, TimerCallbackTriggersMultipleTimes) {
  createTimer();
  service_trigger_enabled_ = true;
  streaming_enabled_ = true;

  EXPECT_CALL(*mock_device_, triggerCapture()).Times(3);
  streamingTimerCallback();
  streamingTimerCallback();
  streamingTimerCallback();
}

// ---------- Timer integration with ROS executor ----------

TEST_F(StreamingLogicTest, TimerFiresThroughExecutor) {
  service_trigger_enabled_ = true;
  streaming_framerate_hz_ = 100.0;
  createTimer();

  int call_count = 0;
  EXPECT_CALL(*mock_device_, triggerCapture())
      .Times(::testing::AtLeast(3))
      .WillRepeatedly([&call_count]() { ++call_count; });

  startStreaming();

  auto start = std::chrono::steady_clock::now();
  while (call_count < 3) {
    rclcpp::spin_some(node_);
    if (std::chrono::steady_clock::now() - start > std::chrono::seconds(2)) {
      FAIL() << "Timer did not fire at least 3 times within 2 seconds";
    }
  }
  EXPECT_THAT(call_count, Ge(3));
}

TEST_F(StreamingLogicTest, CancelledTimerDoesNotFire) {
  service_trigger_enabled_ = true;
  streaming_framerate_hz_ = 100.0;
  createTimer();
  // Timer is created cancelled, never started

  EXPECT_CALL(*mock_device_, triggerCapture()).Times(0);

  rclcpp::spin_some(node_);
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  rclcpp::spin_some(node_);
}

// ---------- Full start-stop-start cycle ----------

TEST_F(StreamingLogicTest, StartStopStartCycle) {
  createTimer();
  service_trigger_enabled_ = true;

  auto r1 = callService(true);
  EXPECT_THAT(r1->success, IsTrue());
  EXPECT_THAT(streaming_enabled_.load(), IsTrue());

  auto r2 = callService(false);
  EXPECT_THAT(r2->success, IsTrue());
  EXPECT_THAT(streaming_enabled_.load(), IsFalse());

  auto r3 = callService(true);
  EXPECT_THAT(r3->success, IsTrue());
  EXPECT_THAT(streaming_enabled_.load(), IsTrue());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
