import os
from datetime import datetime

from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch import LaunchDescription, LaunchContext
from launch.actions import IncludeLaunchDescription, GroupAction, TimerAction, DeclareLaunchArgument, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

PICK_CAMERA_MODE = os.environ.get("PICK_CAMERA_MODE", "trigger")
ROBOT_NAMESPACE = os.environ.get("ROBOT_NAMESPACE", "")
PICK_CAMERA_FW_VERSION = os.environ.get("PICK_CAMERA_FW_VERSION", "1.8.10")
ROS_LOG_DIR = os.environ.get("ROS_LOG_DIR", "~/.ros/log")
ROS_HOME = os.environ.get("ROS_HOME", "~/.ros")

# Include launch files
package_dir = get_package_share_directory('orbbec_camera')
launch_file_dir = os.path.join(package_dir, 'launch')
firmware_upgrade_filepath = f"{ROS_HOME}/camera_firmware/Gemini330_Release_{PICK_CAMERA_FW_VERSION}.bin"
sdk_log_path = ROS_LOG_DIR
sdk_log_filename_prefix = f"{datetime.now().strftime('%Y%m%d_%H%M%S')}_"
sdk_log_filename_suffix = ".log"
sdk_log_level = "warn"


def launch_side_cameras(context: LaunchContext):
    robot_namespace = LaunchConfiguration("robot_namespace").perform(context)

    pick_camera_mode = LaunchConfiguration("pick_camera_mode").perform(context)
    if pick_camera_mode.strip() == "stream":
        print('Running pick cameras in stream mode')
        sync_mode = "standalone"
        service_trigger_enabled = "false"
    elif pick_camera_mode.strip() == "trigger":
        print('Running pick cameras in trigger mode')
        sync_mode = "software_triggering"
        service_trigger_enabled = "true"
    else:
        print('Invalid pick camera mode')
        return []

    launch_include_b_right = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(launch_file_dir, "gemini_330_series.launch.py")
        ),
        launch_arguments={
            "namespace": robot_namespace,
            "camera_name": "inward_b_right_camera",
            "net_device_ip": "192.168.1.30",
            "net_device_port": "8090",
            "exposure_range_mode": "regular",
            "sync_mode": sync_mode,
            "enumerate_net_device": "true",
            "depth_delay_us": "1000",
            "color_delay_us": "1000",
            "enable_color_auto_exposure_priority": "true",
            "service_trigger_enabled": service_trigger_enabled,
            "frames_per_trigger": "2",
            "enable_point_cloud": "false",
            "publish_tf": "false",
            "color_width": "848",
            "color_height": "530",
            "color_fps": "5",
            "depth_width": "848",
            "depth_height": "530",
            "depth_fps": "5",
            "software_trigger_period": "500",
            "diagnostic_period": "10.0",
            "firmware_upgrade_filepath": firmware_upgrade_filepath,
            "expected_firmware_version": PICK_CAMERA_FW_VERSION,
            "log_level": sdk_log_level,
            "log_file_name": sdk_log_filename_prefix + "inward_b_right_camera" + sdk_log_filename_suffix,
            "log_file_path": sdk_log_path,
        }.items(),
    )

    launch_include_b_left = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(launch_file_dir, "gemini_330_series.launch.py")
        ),
        launch_arguments={
            "namespace": robot_namespace,
            "camera_name": "inward_b_left_camera",
            "net_device_ip": "192.168.1.31",
            "net_device_port": "8090",
            "exposure_range_mode": "regular",
            "sync_mode": sync_mode,
            "enumerate_net_device": "true",
            "depth_delay_us": "1000",
            "color_delay_us": "1000",
            "enable_color_auto_exposure_priority": "true",
            "service_trigger_enabled": service_trigger_enabled,
            "frames_per_trigger": "2",
            "enable_point_cloud": "false",
            "publish_tf": "false",
            "color_width": "848",
            "color_height": "530",
            "color_fps": "5",
            "depth_width": "848",
            "depth_height": "530",
            "depth_fps": "5",
            "software_trigger_period": "500",
            "diagnostic_period": "10.0",
            "firmware_upgrade_filepath": firmware_upgrade_filepath,
            "expected_firmware_version": PICK_CAMERA_FW_VERSION,
            "log_level": sdk_log_level,
            "log_file_name": sdk_log_filename_prefix + "inward_b_left_camera" + sdk_log_filename_suffix,
            "log_file_path": sdk_log_path,
        }.items(),
    )

    launch_include_a_right = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(launch_file_dir, "gemini_330_series.launch.py")
        ),
        launch_arguments={
            "namespace": robot_namespace,
            "camera_name": "inward_a_right_camera",
            "net_device_ip": "192.168.1.32",
            "net_device_port": "8090",
            "exposure_range_mode": "regular",
            "sync_mode": sync_mode,
            "enumerate_net_device": "true",
            "depth_delay_us": "1000",
            "color_delay_us": "1000",
            "enable_color_auto_exposure_priority": "true",
            "service_trigger_enabled": service_trigger_enabled,
            "frames_per_trigger": "2",
            "enable_point_cloud": "false",
            "publish_tf": "false",
            "color_width": "848",
            "color_height": "530",
            "color_fps": "5",
            "depth_width": "848",
            "depth_height": "530",
            "depth_fps": "5",
            "software_trigger_period": "500",
            "diagnostic_period": "10.0",
            "firmware_upgrade_filepath": firmware_upgrade_filepath,
            "expected_firmware_version": PICK_CAMERA_FW_VERSION,
            "log_level": sdk_log_level,
            "log_file_name": sdk_log_filename_prefix + "inward_a_right_camera" + sdk_log_filename_suffix,
            "log_file_path": sdk_log_path,
        }.items(),
    )

    launch_include_a_left = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(launch_file_dir, "gemini_330_series.launch.py")
        ),
        launch_arguments={
            "namespace": robot_namespace,
            "camera_name": "inward_a_left_camera",
            "net_device_ip": "192.168.1.33",
            "net_device_port": "8090",
            "exposure_range_mode": "regular",
            "sync_mode": sync_mode,
            "enumerate_net_device": "true",
            "depth_delay_us": "1000",
            "color_delay_us": "1000",
            "enable_color_auto_exposure_priority": "true",
            "service_trigger_enabled": service_trigger_enabled,
            "frames_per_trigger": "2",
            "enable_point_cloud": "false",
            "publish_tf": "false",
            "color_width": "848",
            "color_height": "530",
            "color_fps": "5",
            "depth_width": "848",
            "depth_height": "530",
            "depth_fps": "5",
            "software_trigger_period": "500",
            "diagnostic_period": "10.0",
            "firmware_upgrade_filepath": firmware_upgrade_filepath,
            "expected_firmware_version": PICK_CAMERA_FW_VERSION,
            "log_level": sdk_log_level,
            "log_file_name": sdk_log_filename_prefix + "inward_a_left_camera" + sdk_log_filename_suffix,
            "log_file_path": sdk_log_path,
        }.items(),
    )

    return [TimerAction(period=1.0, actions=[GroupAction([launch_include_b_left])]),
            TimerAction(period=2.0, actions=[GroupAction([launch_include_b_right])]),
            TimerAction(period=3.0, actions=[GroupAction([launch_include_a_left])]),
            TimerAction(period=4.0, actions=[GroupAction([launch_include_a_right])])]


def generate_launch_description():
    pick_camera_mode = DeclareLaunchArgument(
        "pick_camera_mode",
        default_value=PICK_CAMERA_MODE,
        description="Pick camera mode",
        choices=["stream", "trigger"],
    )

    robot_namespace = DeclareLaunchArgument(
        "robot_namespace",
        default_value=ROBOT_NAMESPACE,
    )

    ld = LaunchDescription([
        pick_camera_mode,
        robot_namespace,
        OpaqueFunction(function=launch_side_cameras)
    ])

    return ld
