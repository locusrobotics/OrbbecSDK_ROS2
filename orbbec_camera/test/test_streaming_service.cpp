/*******************************************************************************
 * Tests for the on-demand streaming service.
 *
 * Uses link-time C API stubs (ob_sdk_stubs.cpp) to override the real Orbbec SDK,
 * allowing us to instantiate a real OBCameraNode without hardware.
 ******************************************************************************/

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

#include "orbbec_camera/ob_camera_node.h"
#include "orbbec_camera_msgs/srv/camera_trigger.hpp"

using SetBool = std_srvs::srv::SetBool;
using CameraTrigger = orbbec_camera_msgs::srv::CameraTrigger;
using ::testing::Eq;
using ::testing::HasSubstr;
using ::testing::IsFalse;
using ::testing::IsTrue;

class StreamingServiceTest : public ::testing::Test {
 protected:
  void SetUp() override {
    rclcpp::init(0, nullptr);

    rclcpp::NodeOptions opts;
    // Declare parameters that OBCameraNode::getParameters() expects
    opts.append_parameter_override("service_trigger_enabled", true);
    opts.append_parameter_override("streaming_framerate_hz", 10.0);
    // Disable everything we don't need to minimize construction side effects
    opts.append_parameter_override("enable_color", false);
    opts.append_parameter_override("enable_depth", false);
    opts.append_parameter_override("enable_ir", false);
    opts.append_parameter_override("enable_left_ir", false);
    opts.append_parameter_override("enable_right_ir", false);
    opts.append_parameter_override("enable_gyro", false);
    opts.append_parameter_override("enable_accel", false);
    opts.append_parameter_override("enable_d2c_viewer", false);
    opts.append_parameter_override("enable_colored_point_cloud", false);
    opts.append_parameter_override("enable_point_cloud", false);
    opts.append_parameter_override("enable_soft_filter", false);
    opts.append_parameter_override("enable_frame_sync", false);
    opts.append_parameter_override("publish_tf", false);
    opts.append_parameter_override("enable_sync_output_accel_gyro", false);

    node_ = std::make_shared<rclcpp::Node>("test_camera_node", opts);

    auto device = std::make_shared<ob::Device>(nullptr);
    auto parameters = std::make_shared<orbbec_camera::Parameters>(node_.get());

    camera_node_ = std::make_unique<orbbec_camera::OBCameraNode>(
        node_.get(), device, parameters, /*use_intra_process=*/false);
  }

  void TearDown() override {
    camera_node_.reset();
    node_.reset();
    rclcpp::shutdown();
  }

  std::shared_ptr<SetBool::Response> callSetStreaming(bool data) {
    auto client = node_->create_client<SetBool>("camera/set_streaming");
    auto request = std::make_shared<SetBool::Request>();
    request->data = data;

    auto future = client->async_send_request(request);
    // Spin until the service responds
    auto start = std::chrono::steady_clock::now();
    while (future.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready) {
      rclcpp::spin_some(node_);
      if (std::chrono::steady_clock::now() - start > std::chrono::seconds(5)) {
        ADD_FAILURE() << "Service call timed out";
        return nullptr;
      }
    }
    return future.get();
  }

  std::shared_ptr<CameraTrigger::Response> callTrigger() {
    auto client = node_->create_client<CameraTrigger>("camera/send_service_trigger");
    auto request = std::make_shared<CameraTrigger::Request>();

    auto future = client->async_send_request(request);
    auto start = std::chrono::steady_clock::now();
    while (future.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready) {
      rclcpp::spin_some(node_);
      if (std::chrono::steady_clock::now() - start > std::chrono::seconds(5)) {
        ADD_FAILURE() << "Trigger service call timed out";
        return nullptr;
      }
    }
    return future.get();
  }

  rclcpp::Node::SharedPtr node_;
  std::unique_ptr<orbbec_camera::OBCameraNode> camera_node_;
};

// --- Service accepts start when service_trigger_enabled is true ---

TEST_F(StreamingServiceTest, StartStreamingSucceeds) {
  auto response = callSetStreaming(true);
  ASSERT_NE(response, nullptr);
  EXPECT_THAT(response->success, IsTrue());
  EXPECT_THAT(response->message, Eq("Streaming started"));
}

// --- Service accepts stop ---

TEST_F(StreamingServiceTest, StopStreamingSucceeds) {
  callSetStreaming(true);
  auto response = callSetStreaming(false);
  ASSERT_NE(response, nullptr);
  EXPECT_THAT(response->success, IsTrue());
  EXPECT_THAT(response->message, Eq("Streaming stopped"));
}

// --- Stop when already stopped ---

TEST_F(StreamingServiceTest, StopWhenAlreadyStoppedSucceeds) {
  auto response = callSetStreaming(false);
  ASSERT_NE(response, nullptr);
  EXPECT_THAT(response->success, IsTrue());
  EXPECT_THAT(response->message, Eq("Streaming stopped"));
}

// --- Start is idempotent ---

TEST_F(StreamingServiceTest, DoubleStartSucceeds) {
  auto r1 = callSetStreaming(true);
  ASSERT_NE(r1, nullptr);
  EXPECT_THAT(r1->success, IsTrue());

  auto r2 = callSetStreaming(true);
  ASSERT_NE(r2, nullptr);
  EXPECT_THAT(r2->success, IsTrue());
  EXPECT_THAT(r2->message, Eq("Streaming started"));
}

// --- Full start-stop-start cycle ---

TEST_F(StreamingServiceTest, StartStopStartCycle) {
  auto r1 = callSetStreaming(true);
  ASSERT_NE(r1, nullptr);
  EXPECT_THAT(r1->success, IsTrue());

  auto r2 = callSetStreaming(false);
  ASSERT_NE(r2, nullptr);
  EXPECT_THAT(r2->success, IsTrue());
  EXPECT_THAT(r2->message, Eq("Streaming stopped"));

  auto r3 = callSetStreaming(true);
  ASSERT_NE(r3, nullptr);
  EXPECT_THAT(r3->success, IsTrue());
  EXPECT_THAT(r3->message, Eq("Streaming started"));
}

// --- Trigger during streaming with no cached frames returns failure ---

TEST_F(StreamingServiceTest, TriggerDuringStreamingWithNoFramesFails) {
  callSetStreaming(true);
  auto response = callTrigger();
  ASSERT_NE(response, nullptr);
  EXPECT_THAT(response->success, IsFalse());
  EXPECT_THAT(response->message, HasSubstr("no frames captured yet"));
}

// --- Trigger after stopping streaming does not return stale cached frames ---

TEST_F(StreamingServiceTest, TriggerAfterStopStreamingDoesNotReturnCachedFrames) {
  callSetStreaming(true);
  callSetStreaming(false);
  // After stopping, the trigger should go through the normal (non-streaming) path.
  // With stubbed SDK producing no frames, it will fail with the normal timeout message.
  auto response = callTrigger();
  ASSERT_NE(response, nullptr);
  EXPECT_THAT(response->success, IsFalse());
  EXPECT_THAT(response->message, Eq("Failed to capture images"));
}

// --- Test with service_trigger_enabled=false ---

class StreamingServiceDisabledTest : public ::testing::Test {
 protected:
  void SetUp() override {
    rclcpp::init(0, nullptr);

    rclcpp::NodeOptions opts;
    opts.append_parameter_override("service_trigger_enabled", false);
    opts.append_parameter_override("streaming_framerate_hz", 10.0);
    opts.append_parameter_override("enable_color", false);
    opts.append_parameter_override("enable_depth", false);
    opts.append_parameter_override("enable_ir", false);
    opts.append_parameter_override("enable_left_ir", false);
    opts.append_parameter_override("enable_right_ir", false);
    opts.append_parameter_override("enable_gyro", false);
    opts.append_parameter_override("enable_accel", false);
    opts.append_parameter_override("enable_d2c_viewer", false);
    opts.append_parameter_override("enable_colored_point_cloud", false);
    opts.append_parameter_override("enable_point_cloud", false);
    opts.append_parameter_override("enable_soft_filter", false);
    opts.append_parameter_override("enable_frame_sync", false);
    opts.append_parameter_override("publish_tf", false);
    opts.append_parameter_override("enable_sync_output_accel_gyro", false);

    node_ = std::make_shared<rclcpp::Node>("test_camera_node", opts);

    auto device = std::make_shared<ob::Device>(nullptr);
    auto parameters = std::make_shared<orbbec_camera::Parameters>(node_.get());

    camera_node_ = std::make_unique<orbbec_camera::OBCameraNode>(
        node_.get(), device, parameters, /*use_intra_process=*/false);
  }

  void TearDown() override {
    camera_node_.reset();
    node_.reset();
    rclcpp::shutdown();
  }

  std::shared_ptr<SetBool::Response> callSetStreaming(bool data) {
    auto client = node_->create_client<SetBool>("camera/set_streaming");
    auto request = std::make_shared<SetBool::Request>();
    request->data = data;

    auto future = client->async_send_request(request);
    auto start = std::chrono::steady_clock::now();
    while (future.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready) {
      rclcpp::spin_some(node_);
      if (std::chrono::steady_clock::now() - start > std::chrono::seconds(5)) {
        ADD_FAILURE() << "Service call timed out";
        return nullptr;
      }
    }
    return future.get();
  }

  rclcpp::Node::SharedPtr node_;
  std::unique_ptr<orbbec_camera::OBCameraNode> camera_node_;
};

TEST_F(StreamingServiceDisabledTest, RejectsStartWhenServiceTriggerDisabled) {
  auto response = callSetStreaming(true);
  ASSERT_NE(response, nullptr);
  EXPECT_THAT(response->success, IsFalse());
  EXPECT_THAT(response->message, HasSubstr("service_trigger_enabled"));
}

TEST_F(StreamingServiceDisabledTest, RejectsStopWhenServiceTriggerDisabled) {
  auto response = callSetStreaming(false);
  ASSERT_NE(response, nullptr);
  EXPECT_THAT(response->success, IsFalse());
  EXPECT_THAT(response->message, HasSubstr("service_trigger_enabled"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
