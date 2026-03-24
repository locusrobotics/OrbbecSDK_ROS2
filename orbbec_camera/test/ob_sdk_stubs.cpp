// Stub implementations of the Orbbec SDK C API functions.
// Compiled into the test binary to override real SDK symbols via Linux symbol interposition.
// All stubs return sensible defaults and never produce errors (*error = nullptr).

#include <cstdint>
#include <cstring>

// Define the opaque structs that the SDK uses
struct ob_device_t {};
struct ob_device_info_t {};
struct ob_device_list_t {};
struct ob_sensor_t {};
struct ob_sensor_list_t {};
struct ob_stream_profile_t {};
struct ob_stream_profile_list_t {};
struct ob_filter_t {};
struct ob_filter_list_t {};
struct ob_filter_config_schema_list_t {};
struct ob_pipeline_t {};
struct ob_config_t {};
struct ob_frame_t {};
struct ob_context_t {};
struct ob_record_device_t {};
struct ob_depth_work_mode_list_t {};
struct ob_device_preset_list_t {};
struct ob_camera_param_list_t {};
struct ob_preset_resolution_config_list_t {};
struct ob_device_frame_interleave_list_t {};

// Include SDK headers for correct types (after opaque struct defs so typedefs resolve)
#include "libobsensor/ObSensor.h"

// Static instances returned by pointer-returning stubs
static ob_device_t s_device;
static ob_device_info_t s_device_info;
static ob_device_list_t s_device_list;
static ob_sensor_t s_sensor;
static ob_sensor_list_t s_sensor_list;
static ob_stream_profile_t s_stream_profile;
static ob_stream_profile_list_t s_stream_profile_list;
static ob_filter_t s_filter;
static ob_filter_list_t s_filter_list;
static ob_filter_config_schema_list_t s_filter_config_schema_list;
static ob_pipeline_t s_pipeline;
static ob_config_t s_config;
static ob_frame_t s_frame;
static ob_context_t s_context;
static ob_record_device_t s_record_device;
static ob_depth_work_mode_list_t s_depth_work_mode_list;
static ob_device_preset_list_t s_device_preset_list;
static ob_camera_param_list_t s_camera_param_list;
static ob_preset_resolution_config_list_t s_preset_resolution_config_list;
static ob_device_frame_interleave_list_t s_device_frame_interleave_list;

// Helper: clear error pointer
#define SAFE_ERROR(err) do { if (err) *err = nullptr; } while(0)

extern "C" {

// ============================================================================
// Version.h
// ============================================================================
int ob_get_version(void) { return 0; }
int ob_get_major_version(void) { return 0; }
int ob_get_minor_version(void) { return 0; }
int ob_get_patch_version(void) { return 0; }
const char *ob_get_stage_version(void) { return ""; }

// ============================================================================
// Error.h
// ============================================================================
ob_error *ob_create_error(ob_status status, const char *message, const char *function, const char *args, ob_exception_type exception_type) {
    (void)status; (void)message; (void)function; (void)args; (void)exception_type;
    return nullptr;
}
ob_status ob_error_get_status(const ob_error *error) { (void)error; return OB_STATUS_OK; }
const char *ob_error_get_message(const ob_error *error) { (void)error; return ""; }
const char *ob_error_get_function(const ob_error *error) { (void)error; return ""; }
const char *ob_error_get_args(const ob_error *error) { (void)error; return ""; }
ob_exception_type ob_error_get_exception_type(const ob_error *error) { (void)error; return OB_EXCEPTION_TYPE_UNKNOWN; }
void ob_delete_error(ob_error *error) { (void)error; }

// ============================================================================
// Context.h
// ============================================================================
ob_context *ob_create_context(ob_error **error) { SAFE_ERROR(error); return &s_context; }
ob_context *ob_create_context_with_config(const char *config_file_path, ob_error **error) {
    (void)config_file_path; SAFE_ERROR(error); return &s_context;
}
void ob_delete_context(ob_context *context, ob_error **error) { (void)context; SAFE_ERROR(error); }
ob_device_list *ob_query_device_list(ob_context *context, ob_error **error) {
    (void)context; SAFE_ERROR(error); return &s_device_list;
}
void ob_enable_net_device_enumeration(ob_context *context, bool enable, ob_error **error) {
    (void)context; (void)enable; SAFE_ERROR(error);
}
bool ob_force_ip_config(const char *macAddress, ob_net_ip_config config, ob_error **error) {
    (void)macAddress; (void)config; SAFE_ERROR(error); return false;
}
ob_device *ob_create_net_device(ob_context *context, const char *address, uint16_t port, ob_error **error) {
    (void)context; (void)address; (void)port; SAFE_ERROR(error); return &s_device;
}
ob_device *ob_create_net_device_ex(ob_context *context, const char *address, uint16_t port, ob_device_access_mode accessMode, ob_error **error) {
    (void)context; (void)address; (void)port; (void)accessMode; SAFE_ERROR(error); return &s_device;
}
void ob_set_device_changed_callback(ob_context *context, ob_device_changed_callback callback, void *user_data, ob_error **error) {
    (void)context; (void)callback; (void)user_data; SAFE_ERROR(error);
}
ob_callback_id ob_register_device_changed_callback(ob_context *context, ob_device_changed_callback callback, void *user_data, ob_error **error) {
    (void)context; (void)callback; (void)user_data; SAFE_ERROR(error); return 0;
}
void ob_unregister_device_changed_callback(ob_context *context, ob_callback_id callback_id, ob_error **error) {
    (void)context; (void)callback_id; SAFE_ERROR(error);
}
void ob_enable_device_clock_sync(ob_context *context, uint64_t repeat_interval_msec, ob_error **error) {
    (void)context; (void)repeat_interval_msec; SAFE_ERROR(error);
}
void ob_free_idle_memory(ob_context *context, ob_error **error) {
    (void)context; SAFE_ERROR(error);
}
void ob_set_uvc_backend_type(ob_context *context, ob_uvc_backend_type backend_type, ob_error **error) {
    (void)context; (void)backend_type; SAFE_ERROR(error);
}
void ob_set_logger_severity(ob_log_severity severity, ob_error **error) {
    (void)severity; SAFE_ERROR(error);
}
void ob_set_logger_to_file(ob_log_severity severity, const char *directory, ob_error **error) {
    (void)severity; (void)directory; SAFE_ERROR(error);
}
void ob_set_logger_file_name(const char *file_name, ob_error **error) {
    (void)file_name; SAFE_ERROR(error);
}
void ob_set_logger_to_callback(ob_log_severity severity, ob_log_callback callback, void *user_data, ob_error **error) {
    (void)severity; (void)callback; (void)user_data; SAFE_ERROR(error);
}
void ob_set_logger_to_console(ob_log_severity severity, ob_error **error) {
    (void)severity; SAFE_ERROR(error);
}
void ob_log_external_message(ob_log_severity severity, const char *module, const char *message, const char *file, const char *func, int line,
                             ob_error **error) {
    (void)severity; (void)module; (void)message; (void)file; (void)func; (void)line; SAFE_ERROR(error);
}
void ob_set_extensions_directory(const char *directory, ob_error **error) {
    (void)directory; SAFE_ERROR(error);
}

// ============================================================================
// Device.h
// ============================================================================
void ob_delete_device(ob_device *device, ob_error **error) { (void)device; SAFE_ERROR(error); }

ob_sensor_list *ob_device_get_sensor_list(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return &s_sensor_list;
}

ob_sensor *ob_device_get_sensor(ob_device *device, ob_sensor_type type, ob_error **error) {
    (void)device; (void)type; SAFE_ERROR(error); return nullptr;
}

void ob_device_set_int_property(ob_device *device, ob_property_id property_id, int32_t value, ob_error **error) {
    (void)device; (void)property_id; (void)value; SAFE_ERROR(error);
}
int32_t ob_device_get_int_property(ob_device *device, ob_property_id property_id, ob_error **error) {
    (void)device; (void)property_id; SAFE_ERROR(error); return 0;
}
ob_int_property_range ob_device_get_int_property_range(ob_device *device, ob_property_id property_id, ob_error **error) {
    (void)device; (void)property_id; SAFE_ERROR(error);
    ob_int_property_range r = {};
    return r;
}
void ob_device_set_float_property(ob_device *device, ob_property_id property_id, float value, ob_error **error) {
    (void)device; (void)property_id; (void)value; SAFE_ERROR(error);
}
float ob_device_get_float_property(ob_device *device, ob_property_id property_id, ob_error **error) {
    (void)device; (void)property_id; SAFE_ERROR(error); return 0.0f;
}
ob_float_property_range ob_device_get_float_property_range(ob_device *device, ob_property_id property_id, ob_error **error) {
    (void)device; (void)property_id; SAFE_ERROR(error);
    ob_float_property_range r = {};
    return r;
}
void ob_device_set_bool_property(ob_device *device, ob_property_id property_id, bool value, ob_error **error) {
    (void)device; (void)property_id; (void)value; SAFE_ERROR(error);
}
bool ob_device_get_bool_property(ob_device *device, ob_property_id property_id, ob_error **error) {
    (void)device; (void)property_id; SAFE_ERROR(error); return false;
}
ob_bool_property_range ob_device_get_bool_property_range(ob_device *device, ob_property_id property_id, ob_error **error) {
    (void)device; (void)property_id; SAFE_ERROR(error);
    ob_bool_property_range r = {};
    return r;
}
void ob_device_set_structured_data(ob_device *device, ob_property_id property_id, const uint8_t *data, uint32_t data_size, ob_error **error) {
    (void)device; (void)property_id; (void)data; (void)data_size; SAFE_ERROR(error);
}
void ob_device_get_structured_data(ob_device *device, ob_property_id property_id, uint8_t *data, uint32_t *data_size, ob_error **error) {
    (void)device; (void)property_id; (void)data;
    if (data_size) *data_size = 0;
    SAFE_ERROR(error);
}
void ob_device_get_raw_data(ob_device *device, ob_property_id property_id, ob_get_data_callback cb, void *user_data, ob_error **error) {
    (void)device; (void)property_id; (void)cb; (void)user_data; SAFE_ERROR(error);
}
void ob_device_write_customer_data(ob_device *device, const void *data, uint32_t data_size, ob_error **error) {
    (void)device; (void)data; (void)data_size; SAFE_ERROR(error);
}
void ob_device_read_customer_data(ob_device *device, void *data, uint32_t *data_size, ob_error **error) {
    (void)device; (void)data;
    if (data_size) *data_size = 0;
    SAFE_ERROR(error);
}
uint32_t ob_device_get_supported_property_count(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return 0;
}
ob_property_item ob_device_get_supported_property_item(const ob_device *device, uint32_t index, ob_error **error) {
    (void)device; (void)index; SAFE_ERROR(error);
    ob_property_item item = {};
    return item;
}
bool ob_device_is_property_supported(const ob_device *device, ob_property_id property_id, ob_permission_type permission, ob_error **error) {
    (void)device; (void)property_id; (void)permission; SAFE_ERROR(error); return false;
}
bool ob_device_is_global_timestamp_supported(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return false;
}
void ob_device_enable_global_timestamp(ob_device *device, bool enable, ob_error **error) {
    (void)device; (void)enable; SAFE_ERROR(error);
}
void ob_device_update_firmware(ob_device *device, const char *path, ob_device_fw_update_callback callback, bool async, void *user_data,
                               ob_error **error) {
    (void)device; (void)path; (void)callback; (void)async; (void)user_data; SAFE_ERROR(error);
}
void ob_device_update_firmware_from_data(ob_device *device, const uint8_t *data, uint32_t data_size, ob_device_fw_update_callback callback,
                                         bool async, void *user_data, ob_error **error) {
    (void)device; (void)data; (void)data_size; (void)callback; (void)async; (void)user_data; SAFE_ERROR(error);
}
void ob_device_update_optional_depth_presets(ob_device *device, const char file_path_list[][OB_PATH_MAX], uint8_t path_count,
                                             ob_device_fw_update_callback callback, void *user_data, ob_error **error) {
    (void)device; (void)file_path_list; (void)path_count; (void)callback; (void)user_data; SAFE_ERROR(error);
}
void ob_device_reboot(ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error);
}
ob_device_state ob_device_get_device_state(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return 0;
}
void ob_device_set_state_changed_callback(ob_device *device, ob_device_state_callback callback, void *user_data, ob_error **error) {
    (void)device; (void)callback; (void)user_data; SAFE_ERROR(error);
}
void ob_device_enable_heartbeat(ob_device *device, bool enable, ob_error **error) {
    (void)device; (void)enable; SAFE_ERROR(error);
}
void ob_device_send_and_receive_data(ob_device *device, const uint8_t *send_data, uint32_t send_data_size, uint8_t *receive_data,
                                     uint32_t *receive_data_size, ob_error **error) {
    (void)device; (void)send_data; (void)send_data_size; (void)receive_data;
    if (receive_data_size) *receive_data_size = 0;
    SAFE_ERROR(error);
}

// Device info
ob_device_info *ob_device_get_device_info(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return &s_device_info;
}
void ob_delete_device_info(ob_device_info *info, ob_error **error) { (void)info; SAFE_ERROR(error); }
const char *ob_device_info_get_name(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "MockDevice";
}
int ob_device_info_get_pid(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return 0;
}
int ob_device_info_get_vid(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return 0;
}
const char *ob_device_info_get_uid(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "mock-uid";
}
const char *ob_device_info_get_serial_number(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "MOCK_SERIAL";
}
const char *ob_device_info_get_firmware_version(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "0.0.0";
}
const char *ob_device_info_get_connection_type(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "Ethernet";
}
const char *ob_device_info_get_ip_address(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "0.0.0.0";
}
const char *ob_device_info_get_subnet_mask(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "255.255.255.0";
}
const char *ob_device_info_get_gateway(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "0.0.0.0";
}
const char *ob_device_info_get_hardware_version(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "0.0";
}
bool ob_device_is_extension_info_exist(const ob_device *device, const char *info_key, ob_error **error) {
    (void)device; (void)info_key; SAFE_ERROR(error); return false;
}
const char *ob_device_get_extension_info(const ob_device *device, const char *info_key, ob_error **error) {
    (void)device; (void)info_key; SAFE_ERROR(error); return "";
}
const char *ob_device_info_get_supported_min_sdk_version(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "0.0.0";
}
const char *ob_device_info_get_asicName(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return "Mock";
}
ob_device_type ob_device_info_get_device_type(const ob_device_info *info, ob_error **error) {
    (void)info; SAFE_ERROR(error); return static_cast<ob_device_type>(0);
}

// Device list
void ob_delete_device_list(ob_device_list *list, ob_error **error) { (void)list; SAFE_ERROR(error); }
uint32_t ob_device_list_get_count(const ob_device_list *list, ob_error **error) {
    (void)list; SAFE_ERROR(error); return 0;
}
const char *ob_device_list_get_device_name(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "MockDevice";
}
int ob_device_list_get_device_pid(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return 0;
}
int ob_device_list_get_device_vid(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return 0;
}
const char *ob_device_list_get_device_uid(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "mock-uid";
}
const char *ob_device_list_get_device_serial_number(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "MOCK_SERIAL";
}
const char *ob_device_list_get_device_connection_type(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "Ethernet";
}
const char *ob_device_list_get_device_ip_address(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "0.0.0.0";
}
const char *ob_device_list_get_device_subnet_mask(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "255.255.255.0";
}
const char *ob_device_list_get_device_gateway(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "0.0.0.0";
}
const char *ob_device_list_get_device_local_mac(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "0:0:0:0:0:0";
}
const char *ob_device_list_get_device_local_ip(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "0.0.0.0";
}
uint8_t ob_device_list_get_device_local_subnet_length(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return 0;
}
const char *ob_device_list_get_device_local_gateway(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return "0.0.0.0";
}
ob_device *ob_device_list_get_device(const ob_device_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error); return &s_device;
}
ob_device *ob_device_list_get_device_ex(const ob_device_list *list, uint32_t index, ob_device_access_mode accessMode, ob_error **error) {
    (void)list; (void)index; (void)accessMode; SAFE_ERROR(error); return &s_device;
}
ob_device *ob_device_list_get_device_by_serial_number(const ob_device_list *list, const char *serial_number, ob_error **error) {
    (void)list; (void)serial_number; SAFE_ERROR(error); return &s_device;
}
ob_device *ob_device_list_get_device_by_serial_number_ex(const ob_device_list *list, const char *serial_number, ob_device_access_mode accessMode,
                                                         ob_error **error) {
    (void)list; (void)serial_number; (void)accessMode; SAFE_ERROR(error); return &s_device;
}
ob_device *ob_device_list_get_device_by_uid(const ob_device_list *list, const char *uid, ob_error **error) {
    (void)list; (void)uid; SAFE_ERROR(error); return &s_device;
}
ob_device *ob_device_list_get_device_by_uid_ex(const ob_device_list *list, const char *uid, ob_device_access_mode accessMode, ob_error **error) {
    (void)list; (void)uid; (void)accessMode; SAFE_ERROR(error); return &s_device;
}

// Camera param list
ob_camera_param_list *ob_device_get_calibration_camera_param_list(ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return &s_camera_param_list;
}
uint32_t ob_camera_param_list_get_count(ob_camera_param_list *param_list, ob_error **error) {
    (void)param_list; SAFE_ERROR(error); return 0;
}
ob_camera_param ob_camera_param_list_get_param(ob_camera_param_list *param_list, uint32_t index, ob_error **error) {
    (void)param_list; (void)index; SAFE_ERROR(error);
    ob_camera_param p = {};
    return p;
}
void ob_delete_camera_param_list(ob_camera_param_list *param_list, ob_error **error) {
    (void)param_list; SAFE_ERROR(error);
}

// ============================================================================
// MultipleDevices.h
// ============================================================================
uint16_t ob_device_get_supported_multi_device_sync_mode_bitmap(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return 0;
}
void ob_device_set_multi_device_sync_config(ob_device *device, const ob_multi_device_sync_config *config, ob_error **error) {
    (void)device; (void)config; SAFE_ERROR(error);
}
ob_multi_device_sync_config ob_device_get_multi_device_sync_config(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error);
    ob_multi_device_sync_config c = {};
    return c;
}
void ob_device_trigger_capture(ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error);
}
void ob_device_set_timestamp_reset_config(ob_device *device, const ob_device_timestamp_reset_config *config, ob_error **error) {
    (void)device; (void)config; SAFE_ERROR(error);
}
ob_device_timestamp_reset_config ob_device_get_timestamp_reset_config(ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error);
    ob_device_timestamp_reset_config c = {};
    return c;
}
void ob_device_timestamp_reset(ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error);
}
void ob_device_timer_sync_with_host(ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error);
}

// ============================================================================
// Advanced.h
// ============================================================================
ob_depth_work_mode ob_device_get_current_depth_work_mode(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error);
    ob_depth_work_mode m = {};
    return m;
}
const char *ob_device_get_current_depth_work_mode_name(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return "";
}
ob_status ob_device_switch_depth_work_mode(ob_device *device, const ob_depth_work_mode *work_mode, ob_error **error) {
    (void)device; (void)work_mode; SAFE_ERROR(error); return OB_STATUS_OK;
}
ob_status ob_device_switch_depth_work_mode_by_name(ob_device *device, const char *mode_name, ob_error **error) {
    (void)device; (void)mode_name; SAFE_ERROR(error); return OB_STATUS_OK;
}
ob_depth_work_mode_list *ob_device_get_depth_work_mode_list(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return &s_depth_work_mode_list;
}
uint32_t ob_depth_work_mode_list_get_count(const ob_depth_work_mode_list *work_mode_list, ob_error **error) {
    (void)work_mode_list; SAFE_ERROR(error); return 0;
}
ob_depth_work_mode ob_depth_work_mode_list_get_item(const ob_depth_work_mode_list *work_mode_list, uint32_t index, ob_error **error) {
    (void)work_mode_list; (void)index; SAFE_ERROR(error);
    ob_depth_work_mode m = {};
    return m;
}
void ob_delete_depth_work_mode_list(ob_depth_work_mode_list *work_mode_list, ob_error **error) {
    (void)work_mode_list; SAFE_ERROR(error);
}

const char *ob_device_get_current_preset_name(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return "";
}
void ob_device_load_preset(ob_device *device, const char *preset_name, ob_error **error) {
    (void)device; (void)preset_name; SAFE_ERROR(error);
}
void ob_device_load_preset_from_json_file(ob_device *device, const char *json_file_path, ob_error **error) {
    (void)device; (void)json_file_path; SAFE_ERROR(error);
}
void ob_device_load_preset_from_json_data(ob_device *device, const char *presetName, const uint8_t *data, uint32_t size, ob_error **error) {
    (void)device; (void)presetName; (void)data; (void)size; SAFE_ERROR(error);
}
void ob_device_export_current_settings_as_preset_json_file(ob_device *device, const char *json_file_path, ob_error **error) {
    (void)device; (void)json_file_path; SAFE_ERROR(error);
}
void ob_device_export_current_settings_as_preset_json_data(ob_device *device, const char *presetName, const uint8_t **data, uint32_t *dataSize,
                                                           ob_error **error) {
    (void)device; (void)presetName;
    if (data) *data = nullptr;
    if (dataSize) *dataSize = 0;
    SAFE_ERROR(error);
}
ob_device_preset_list *ob_device_get_available_preset_list(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return &s_device_preset_list;
}
void ob_delete_preset_list(ob_device_preset_list *preset_list, ob_error **error) {
    (void)preset_list; SAFE_ERROR(error);
}
uint32_t ob_device_preset_list_get_count(const ob_device_preset_list *preset_list, ob_error **error) {
    (void)preset_list; SAFE_ERROR(error); return 0;
}
const char *ob_device_preset_list_get_name(const ob_device_preset_list *preset_list, uint32_t index, ob_error **error) {
    (void)preset_list; (void)index; SAFE_ERROR(error); return "";
}
bool ob_device_preset_list_has_preset(const ob_device_preset_list *preset_list, const char *preset_name, ob_error **error) {
    (void)preset_list; (void)preset_name; SAFE_ERROR(error); return false;
}

bool ob_device_is_frame_interleave_supported(const ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return false;
}
void ob_device_load_frame_interleave(ob_device *device, const char *frame_interleave_name, ob_error **error) {
    (void)device; (void)frame_interleave_name; SAFE_ERROR(error);
}
ob_device_frame_interleave_list *ob_device_get_available_frame_interleave_list(ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return &s_device_frame_interleave_list;
}
void ob_delete_frame_interleave_list(ob_device_frame_interleave_list *frame_interleave_list, ob_error **error) {
    (void)frame_interleave_list; SAFE_ERROR(error);
}
uint32_t ob_device_frame_interleave_list_get_count(ob_device_frame_interleave_list *frame_interleave_list, ob_error **error) {
    (void)frame_interleave_list; SAFE_ERROR(error); return 0;
}
const char *ob_device_frame_interleave_list_get_name(ob_device_frame_interleave_list *frame_interleave_list, uint32_t index, ob_error **error) {
    (void)frame_interleave_list; (void)index; SAFE_ERROR(error); return "";
}
bool ob_device_frame_interleave_list_has_frame_interleave(ob_device_frame_interleave_list *frame_interleave_list, const char *frame_interleave_name,
                                                          ob_error **error) {
    (void)frame_interleave_list; (void)frame_interleave_name; SAFE_ERROR(error); return false;
}

ob_preset_resolution_config_list *ob_device_get_available_preset_resolution_config_list(ob_device *device, ob_error **error) {
    (void)device; SAFE_ERROR(error); return &s_preset_resolution_config_list;
}
uint32_t ob_device_preset_resolution_config_get_count(ob_preset_resolution_config_list *list, ob_error **error) {
    (void)list; SAFE_ERROR(error); return 0;
}
OBPresetResolutionConfig ob_device_preset_resolution_config_list_get_item(const ob_preset_resolution_config_list *list, uint32_t index, ob_error **error) {
    (void)list; (void)index; SAFE_ERROR(error);
    OBPresetResolutionConfig c = {};
    return c;
}
void ob_delete_preset_resolution_config_list(ob_preset_resolution_config_list *list, ob_error **error) {
    (void)list; SAFE_ERROR(error);
}

// ============================================================================
// Sensor.h
// ============================================================================
ob_sensor_type ob_sensor_get_type(const ob_sensor *sensor, ob_error **error) {
    (void)sensor; SAFE_ERROR(error); return OB_SENSOR_UNKNOWN;
}
ob_stream_profile_list *ob_sensor_get_stream_profile_list(const ob_sensor *sensor, ob_error **error) {
    (void)sensor; SAFE_ERROR(error); return &s_stream_profile_list;
}
void ob_sensor_start(ob_sensor *sensor, const ob_stream_profile *profile, ob_frame_callback callback, void *user_data, ob_error **error) {
    (void)sensor; (void)profile; (void)callback; (void)user_data; SAFE_ERROR(error);
}
void ob_sensor_stop(ob_sensor *sensor, ob_error **error) {
    (void)sensor; SAFE_ERROR(error);
}
void ob_sensor_switch_profile(ob_sensor *sensor, ob_stream_profile *profile, ob_error **error) {
    (void)sensor; (void)profile; SAFE_ERROR(error);
}
void ob_delete_sensor(ob_sensor *sensor, ob_error **error) { (void)sensor; SAFE_ERROR(error); }
ob_filter_list *ob_sensor_create_recommended_filter_list(const ob_sensor *sensor, ob_error **error) {
    (void)sensor; SAFE_ERROR(error); return &s_filter_list;
}
uint32_t ob_sensor_list_get_count(const ob_sensor_list *sensor_list, ob_error **error) {
    (void)sensor_list; SAFE_ERROR(error); return 0;
}
ob_sensor_type ob_sensor_list_get_sensor_type(const ob_sensor_list *sensor_list, uint32_t index, ob_error **error) {
    (void)sensor_list; (void)index; SAFE_ERROR(error); return OB_SENSOR_UNKNOWN;
}
ob_sensor *ob_sensor_list_get_sensor_by_type(const ob_sensor_list *sensor_list, ob_sensor_type sensorType, ob_error **error) {
    (void)sensor_list; (void)sensorType; SAFE_ERROR(error); return nullptr;
}
ob_sensor *ob_sensor_list_get_sensor(const ob_sensor_list *sensor_list, uint32_t index, ob_error **error) {
    (void)sensor_list; (void)index; SAFE_ERROR(error); return &s_sensor;
}
void ob_delete_sensor_list(ob_sensor_list *sensor_list, ob_error **error) {
    (void)sensor_list; SAFE_ERROR(error);
}

// ============================================================================
// StreamProfile.h
// ============================================================================
ob_stream_profile *ob_create_stream_profile(ob_stream_type type, ob_format format, ob_error **error) {
    (void)type; (void)format; SAFE_ERROR(error); return &s_stream_profile;
}
ob_stream_profile *ob_create_video_stream_profile(ob_stream_type type, ob_format format, uint32_t width, uint32_t height, uint32_t fps,
                                                  ob_error **error) {
    (void)type; (void)format; (void)width; (void)height; (void)fps; SAFE_ERROR(error); return &s_stream_profile;
}
ob_stream_profile *ob_create_accel_stream_profile(ob_accel_full_scale_range full_scale_range, ob_accel_sample_rate sample_rate, ob_error **error) {
    (void)full_scale_range; (void)sample_rate; SAFE_ERROR(error); return &s_stream_profile;
}
ob_stream_profile *ob_create_gyro_stream_profile(ob_gyro_full_scale_range full_scale_range, ob_gyro_sample_rate sample_rate, ob_error **error) {
    (void)full_scale_range; (void)sample_rate; SAFE_ERROR(error); return &s_stream_profile;
}
ob_stream_profile *ob_create_lidar_stream_profile(ob_lidar_scan_rate scan_rate, ob_format format, ob_error **error) {
    (void)scan_rate; (void)format; SAFE_ERROR(error); return &s_stream_profile;
}
ob_stream_profile *ob_create_stream_profile_from_other_stream_profile(const ob_stream_profile *srcProfile, ob_error **error) {
    (void)srcProfile; SAFE_ERROR(error); return &s_stream_profile;
}
ob_stream_profile *ob_create_stream_profile_with_new_format(const ob_stream_profile *profile, ob_format new_format, ob_error **error) {
    (void)profile; (void)new_format; SAFE_ERROR(error); return &s_stream_profile;
}
void ob_delete_stream_profile(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error);
}
ob_format ob_stream_profile_get_format(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return OB_FORMAT_UNKNOWN;
}
void ob_stream_profile_set_format(ob_stream_profile *profile, ob_format format, ob_error **error) {
    (void)profile; (void)format; SAFE_ERROR(error);
}
ob_stream_type ob_stream_profile_get_type(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return OB_STREAM_UNKNOWN;
}
void ob_stream_profile_set_type(const ob_stream_profile *profile, ob_stream_type type, ob_error **error) {
    (void)profile; (void)type; SAFE_ERROR(error);
}
ob_extrinsic ob_stream_profile_get_extrinsic_to(const ob_stream_profile *source, ob_stream_profile *target, ob_error **error) {
    (void)source; (void)target; SAFE_ERROR(error);
    ob_extrinsic e = {};
    return e;
}
void ob_stream_profile_set_extrinsic_to(ob_stream_profile *source, const ob_stream_profile *target, ob_extrinsic extrinsic, ob_error **error) {
    (void)source; (void)target; (void)extrinsic; SAFE_ERROR(error);
}
void ob_stream_profile_set_extrinsic_to_type(ob_stream_profile *source, const ob_stream_type type, ob_extrinsic extrinsic, ob_error **error) {
    (void)source; (void)type; (void)extrinsic; SAFE_ERROR(error);
}
uint32_t ob_video_stream_profile_get_fps(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return 0;
}
uint32_t ob_video_stream_profile_get_width(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return 0;
}
void ob_video_stream_profile_set_width(ob_stream_profile *profile, uint32_t width, ob_error **error) {
    (void)profile; (void)width; SAFE_ERROR(error);
}
uint32_t ob_video_stream_profile_get_height(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return 0;
}
void ob_video_stream_profile_set_height(ob_stream_profile *profile, uint32_t height, ob_error **error) {
    (void)profile; (void)height; SAFE_ERROR(error);
}
ob_camera_intrinsic ob_video_stream_profile_get_intrinsic(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error);
    ob_camera_intrinsic i = {};
    return i;
}
void ob_video_stream_profile_set_intrinsic(ob_stream_profile *profile, ob_camera_intrinsic intrinsic, ob_error **error) {
    (void)profile; (void)intrinsic; SAFE_ERROR(error);
}
ob_camera_distortion ob_video_stream_profile_get_distortion(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error);
    ob_camera_distortion d = {};
    return d;
}
void ob_video_stream_profile_set_distortion(ob_stream_profile *profile, ob_camera_distortion distortion, ob_error **error) {
    (void)profile; (void)distortion; SAFE_ERROR(error);
}
ob_disparity_param ob_disparity_based_stream_profile_get_disparity_param(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error);
    ob_disparity_param p = {};
    return p;
}
void ob_disparity_based_stream_profile_set_disparity_param(ob_stream_profile *profile, ob_disparity_param param, ob_error **error) {
    (void)profile; (void)param; SAFE_ERROR(error);
}
ob_accel_full_scale_range ob_accel_stream_profile_get_full_scale_range(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return static_cast<ob_accel_full_scale_range>(0);
}
ob_accel_sample_rate ob_accel_stream_profile_get_sample_rate(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return static_cast<ob_accel_sample_rate>(0);
}
ob_accel_intrinsic ob_accel_stream_profile_get_intrinsic(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error);
    ob_accel_intrinsic i = {};
    return i;
}
void ob_accel_stream_profile_set_intrinsic(ob_stream_profile *profile, ob_accel_intrinsic intrinsic, ob_error **error) {
    (void)profile; (void)intrinsic; SAFE_ERROR(error);
}
ob_gyro_full_scale_range ob_gyro_stream_profile_get_full_scale_range(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return static_cast<ob_gyro_full_scale_range>(0);
}
ob_gyro_sample_rate ob_gyro_stream_profile_get_sample_rate(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return static_cast<ob_gyro_sample_rate>(0);
}
ob_gyro_intrinsic ob_gyro_stream_get_intrinsic(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error);
    ob_gyro_intrinsic i = {};
    return i;
}
void ob_gyro_stream_set_intrinsic(ob_stream_profile *profile, ob_gyro_intrinsic intrinsic, ob_error **error) {
    (void)profile; (void)intrinsic; SAFE_ERROR(error);
}
ob_lidar_scan_rate ob_lidar_stream_profile_get_scan_rate(const ob_stream_profile *profile, ob_error **error) {
    (void)profile; SAFE_ERROR(error); return static_cast<ob_lidar_scan_rate>(0);
}
uint32_t ob_stream_profile_list_get_count(const ob_stream_profile_list *profile_list, ob_error **error) {
    (void)profile_list; SAFE_ERROR(error); return 0;
}
ob_stream_profile *ob_stream_profile_list_get_profile(const ob_stream_profile_list *profile_list, int index, ob_error **error) {
    (void)profile_list; (void)index; SAFE_ERROR(error); return &s_stream_profile;
}
ob_stream_profile *ob_stream_profile_list_get_video_stream_profile(const ob_stream_profile_list *profile_list, int width, int height,
                                                                   ob_format format, int fps, ob_error **error) {
    (void)profile_list; (void)width; (void)height; (void)format; (void)fps; SAFE_ERROR(error); return nullptr;
}
ob_stream_profile *ob_stream_profile_list_get_accel_stream_profile(const ob_stream_profile_list *profile_list,
                                                                   ob_accel_full_scale_range full_scale_range, ob_accel_sample_rate sample_rate,
                                                                   ob_error **error) {
    (void)profile_list; (void)full_scale_range; (void)sample_rate; SAFE_ERROR(error); return nullptr;
}
ob_stream_profile *ob_stream_profile_list_get_gyro_stream_profile(const ob_stream_profile_list *profile_list,
                                                                  ob_gyro_full_scale_range full_scale_range, ob_gyro_sample_rate sample_rate,
                                                                  ob_error **error) {
    (void)profile_list; (void)full_scale_range; (void)sample_rate; SAFE_ERROR(error); return nullptr;
}
ob_stream_profile *ob_stream_profile_list_get_lidar_stream_profile(const ob_stream_profile_list *profile_list, ob_lidar_scan_rate scan_rate,
                                                                   ob_format format, ob_error **error) {
    (void)profile_list; (void)scan_rate; (void)format; SAFE_ERROR(error); return nullptr;
}
void ob_delete_stream_profile_list(const ob_stream_profile_list *profile_list, ob_error **error) {
    (void)profile_list; SAFE_ERROR(error);
}

// ============================================================================
// Filter.h
// ============================================================================
ob_filter *ob_create_filter(const char *name, ob_error **error) {
    (void)name; SAFE_ERROR(error); return &s_filter;
}
const char *ob_filter_get_name(const ob_filter *filter, ob_error **error) {
    (void)filter; SAFE_ERROR(error); return "mock_filter";
}
const char *ob_filter_get_vendor_specific_code(const char *name, ob_error **error) {
    (void)name; SAFE_ERROR(error); return "";
}
ob_filter *ob_create_private_filter(const char *name, const char *activation_key, ob_error **error) {
    (void)name; (void)activation_key; SAFE_ERROR(error); return &s_filter;
}
void ob_delete_filter(ob_filter *filter, ob_error **error) { (void)filter; SAFE_ERROR(error); }
const char *ob_filter_get_config_schema(const ob_filter *filter, ob_error **error) {
    (void)filter; SAFE_ERROR(error); return "";
}
ob_filter_config_schema_list *ob_filter_get_config_schema_list(const ob_filter *filter, ob_error **error) {
    (void)filter; SAFE_ERROR(error); return &s_filter_config_schema_list;
}
void ob_delete_filter_config_schema_list(ob_filter_config_schema_list *config_schema_list, ob_error **error) {
    (void)config_schema_list; SAFE_ERROR(error);
}
void ob_filter_update_config(ob_filter *filter, uint8_t argc, const char **argv, ob_error **error) {
    (void)filter; (void)argc; (void)argv; SAFE_ERROR(error);
}
double ob_filter_get_config_value(const ob_filter *filter, const char *config_name, ob_error **error) {
    (void)filter; (void)config_name; SAFE_ERROR(error); return 0.0;
}
void ob_filter_set_config_value(ob_filter *filter, const char *config_name, double value, ob_error **error) {
    (void)filter; (void)config_name; (void)value; SAFE_ERROR(error);
}
void ob_filter_reset(ob_filter *filter, ob_error **error) { (void)filter; SAFE_ERROR(error); }
void ob_filter_enable(ob_filter *filter, bool enable, ob_error **error) {
    (void)filter; (void)enable; SAFE_ERROR(error);
}
bool ob_filter_is_enabled(const ob_filter *filter, ob_error **error) {
    (void)filter; SAFE_ERROR(error); return false;
}
ob_frame *ob_filter_process(ob_filter *filter, const ob_frame *frame, ob_error **error) {
    (void)filter; (void)frame; SAFE_ERROR(error); return nullptr;
}
void ob_filter_set_callback(ob_filter *filter, ob_filter_callback callback, void *user_data, ob_error **error) {
    (void)filter; (void)callback; (void)user_data; SAFE_ERROR(error);
}
void ob_filter_push_frame(ob_filter *filter, const ob_frame *frame, ob_error **error) {
    (void)filter; (void)frame; SAFE_ERROR(error);
}
uint32_t ob_filter_list_get_count(const ob_filter_list *filter_list, ob_error **error) {
    (void)filter_list; SAFE_ERROR(error); return 0;
}
ob_filter *ob_filter_list_get_filter(const ob_filter_list *filter_list, uint32_t index, ob_error **error) {
    (void)filter_list; (void)index; SAFE_ERROR(error); return &s_filter;
}
void ob_delete_filter_list(ob_filter_list *filter_list, ob_error **error) {
    (void)filter_list; SAFE_ERROR(error);
}
uint32_t ob_filter_config_schema_list_get_count(const ob_filter_config_schema_list *config_schema_list, ob_error **error) {
    (void)config_schema_list; SAFE_ERROR(error); return 0;
}
ob_filter_config_schema_item ob_filter_config_schema_list_get_item(const ob_filter_config_schema_list *config_schema_list, uint32_t index,
                                                                   ob_error **error) {
    (void)config_schema_list; (void)index; SAFE_ERROR(error);
    ob_filter_config_schema_item item = {};
    return item;
}
void ob_align_filter_set_align_to_stream_profile(ob_filter *filter, const ob_stream_profile *align_to_stream_profile, ob_error **error) {
    (void)filter; (void)align_to_stream_profile; SAFE_ERROR(error);
}

// ============================================================================
// Pipeline.h
// ============================================================================
ob_pipeline *ob_create_pipeline(ob_error **error) {
    SAFE_ERROR(error); return &s_pipeline;
}
ob_pipeline *ob_create_pipeline_with_device(const ob_device *dev, ob_error **error) {
    (void)dev; SAFE_ERROR(error); return &s_pipeline;
}
void ob_delete_pipeline(ob_pipeline *pipeline, ob_error **error) { (void)pipeline; SAFE_ERROR(error); }
void ob_pipeline_start(ob_pipeline *pipeline, ob_error **error) { (void)pipeline; SAFE_ERROR(error); }
void ob_pipeline_start_with_config(ob_pipeline *pipeline, const ob_config *config, ob_error **error) {
    (void)pipeline; (void)config; SAFE_ERROR(error);
}
void ob_pipeline_start_with_callback(ob_pipeline *pipeline, const ob_config *config, ob_frameset_callback callback, void *user_data,
                                     ob_error **error) {
    (void)pipeline; (void)config; (void)callback; (void)user_data; SAFE_ERROR(error);
}
void ob_pipeline_stop(ob_pipeline *pipeline, ob_error **error) { (void)pipeline; SAFE_ERROR(error); }
ob_config *ob_pipeline_get_config(const ob_pipeline *pipeline, ob_error **error) {
    (void)pipeline; SAFE_ERROR(error); return &s_config;
}
void ob_pipeline_switch_config(ob_pipeline *pipeline, ob_config *config, ob_error **error) {
    (void)pipeline; (void)config; SAFE_ERROR(error);
}
ob_frame *ob_pipeline_wait_for_frameset(ob_pipeline *pipeline, uint32_t timeout_ms, ob_error **error) {
    (void)pipeline; (void)timeout_ms; SAFE_ERROR(error); return nullptr;
}
ob_device *ob_pipeline_get_device(const ob_pipeline *pipeline, ob_error **error) {
    (void)pipeline; SAFE_ERROR(error); return &s_device;
}
ob_stream_profile_list *ob_pipeline_get_stream_profile_list(const ob_pipeline *pipeline, ob_sensor_type sensorType, ob_error **error) {
    (void)pipeline; (void)sensorType; SAFE_ERROR(error); return &s_stream_profile_list;
}
void ob_pipeline_enable_frame_sync(ob_pipeline *pipeline, ob_error **error) {
    (void)pipeline; SAFE_ERROR(error);
}
void ob_pipeline_disable_frame_sync(ob_pipeline *pipeline, ob_error **error) {
    (void)pipeline; SAFE_ERROR(error);
}
ob_stream_profile_list *ob_get_d2c_depth_profile_list(const ob_pipeline *pipeline, const ob_stream_profile *color_profile, ob_align_mode align_mode,
                                                      ob_error **error) {
    (void)pipeline; (void)color_profile; (void)align_mode; SAFE_ERROR(error); return &s_stream_profile_list;
}
ob_config *ob_create_config(ob_error **error) {
    SAFE_ERROR(error); return &s_config;
}
void ob_delete_config(ob_config *config, ob_error **error) { (void)config; SAFE_ERROR(error); }
void ob_config_enable_stream(ob_config *config, ob_stream_type stream_type, ob_error **error) {
    (void)config; (void)stream_type; SAFE_ERROR(error);
}
void ob_config_enable_all_stream(ob_config *config, ob_error **error) {
    (void)config; SAFE_ERROR(error);
}
void ob_config_enable_stream_with_stream_profile(ob_config *config, const ob_stream_profile *profile, ob_error **error) {
    (void)config; (void)profile; SAFE_ERROR(error);
}
void ob_config_enable_video_stream(ob_config *config, ob_stream_type stream_type, uint32_t width, uint32_t height, uint32_t fps, ob_format format,
                                   ob_error **error) {
    (void)config; (void)stream_type; (void)width; (void)height; (void)fps; (void)format; SAFE_ERROR(error);
}
void ob_config_enable_accel_stream(ob_config *config, ob_accel_full_scale_range full_scale_range, ob_accel_sample_rate sample_rate, ob_error **error) {
    (void)config; (void)full_scale_range; (void)sample_rate; SAFE_ERROR(error);
}
void ob_config_enable_gyro_stream(ob_config *config, ob_gyro_full_scale_range full_scale_range, ob_gyro_sample_rate sample_rate, ob_error **error) {
    (void)config; (void)full_scale_range; (void)sample_rate; SAFE_ERROR(error);
}
void ob_config_enable_lidar_stream(ob_config *config, ob_lidar_scan_rate scan_rate, ob_format format, ob_error **error) {
    (void)config; (void)scan_rate; (void)format; SAFE_ERROR(error);
}
ob_stream_profile_list *ob_config_get_enabled_stream_profile_list(const ob_config *config, ob_error **error) {
    (void)config; SAFE_ERROR(error); return &s_stream_profile_list;
}
void ob_config_disable_stream(ob_config *config, ob_stream_type type, ob_error **error) {
    (void)config; (void)type; SAFE_ERROR(error);
}
void ob_config_disable_all_stream(ob_config *config, ob_error **error) {
    (void)config; SAFE_ERROR(error);
}
void ob_config_set_align_mode(ob_config *config, ob_align_mode mode, ob_error **error) {
    (void)config; (void)mode; SAFE_ERROR(error);
}
void ob_config_set_depth_scale_after_align_require(ob_config *config, bool enable, ob_error **error) {
    (void)config; (void)enable; SAFE_ERROR(error);
}
void ob_config_set_frame_aggregate_output_mode(ob_config *config, ob_frame_aggregate_output_mode mode, ob_error **error) {
    (void)config; (void)mode; SAFE_ERROR(error);
}
ob_camera_param ob_pipeline_get_camera_param(ob_pipeline *pipeline, ob_error **error) {
    (void)pipeline; SAFE_ERROR(error);
    ob_camera_param p = {};
    return p;
}
ob_camera_param ob_pipeline_get_camera_param_with_profile(ob_pipeline *pipeline, uint32_t colorWidth, uint32_t colorHeight, uint32_t depthWidth,
                                                          uint32_t depthHeight, ob_error **error) {
    (void)pipeline; (void)colorWidth; (void)colorHeight; (void)depthWidth; (void)depthHeight; SAFE_ERROR(error);
    ob_camera_param p = {};
    return p;
}
ob_calibration_param ob_pipeline_get_calibration_param(ob_pipeline *pipeline, ob_config *config, ob_error **error) {
    (void)pipeline; (void)config; SAFE_ERROR(error);
    ob_calibration_param p = {};
    return p;
}

// ============================================================================
// Frame.h
// ============================================================================
ob_frame *ob_create_frame(ob_frame_type frame_type, ob_format format, uint32_t data_size, ob_error **error) {
    (void)frame_type; (void)format; (void)data_size; SAFE_ERROR(error); return &s_frame;
}
ob_frame *ob_create_frame_from_other_frame(const ob_frame *other_frame, bool should_copy_data, ob_error **error) {
    (void)other_frame; (void)should_copy_data; SAFE_ERROR(error); return &s_frame;
}
ob_frame *ob_create_frame_from_stream_profile(const ob_stream_profile *stream_profile, ob_error **error) {
    (void)stream_profile; SAFE_ERROR(error); return &s_frame;
}
ob_frame *ob_create_video_frame(ob_frame_type frame_type, ob_format format, uint32_t width, uint32_t height, uint32_t stride_bytes, ob_error **error) {
    (void)frame_type; (void)format; (void)width; (void)height; (void)stride_bytes; SAFE_ERROR(error); return &s_frame;
}
ob_frame *ob_create_frame_from_buffer(ob_frame_type frame_type, ob_format format, uint8_t *buffer, uint32_t buffer_size,
                                      ob_frame_destroy_callback *buffer_destroy_cb, void *buffer_destroy_context, ob_error **error) {
    (void)frame_type; (void)format; (void)buffer; (void)buffer_size; (void)buffer_destroy_cb; (void)buffer_destroy_context; SAFE_ERROR(error);
    return &s_frame;
}
ob_frame *ob_create_video_frame_from_buffer(ob_frame_type frame_type, ob_format format, uint32_t width, uint32_t height, uint32_t stride_bytes,
                                            uint8_t *buffer, uint32_t buffer_size, ob_frame_destroy_callback *buffer_destroy_cb,
                                            void *buffer_destroy_context, ob_error **error) {
    (void)frame_type; (void)format; (void)width; (void)height; (void)stride_bytes;
    (void)buffer; (void)buffer_size; (void)buffer_destroy_cb; (void)buffer_destroy_context; SAFE_ERROR(error);
    return &s_frame;
}
ob_frame *ob_create_frameset(ob_error **error) {
    SAFE_ERROR(error); return &s_frame;
}
void ob_frame_add_ref(const ob_frame *frame, ob_error **error) { (void)frame; SAFE_ERROR(error); }
void ob_delete_frame(const ob_frame *frame, ob_error **error) { (void)frame; SAFE_ERROR(error); }
void ob_frame_copy_info(const ob_frame *src_frame, ob_frame *dst_frame, ob_error **error) {
    (void)src_frame; (void)dst_frame; SAFE_ERROR(error);
}
uint64_t ob_frame_get_index(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
ob_format ob_frame_get_format(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return OB_FORMAT_UNKNOWN;
}
ob_frame_type ob_frame_get_type(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return OB_FRAME_UNKNOWN;
}
uint64_t ob_frame_get_timestamp_us(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
void ob_frame_set_timestamp_us(ob_frame *frame, uint64_t timestamp_us, ob_error **error) {
    (void)frame; (void)timestamp_us; SAFE_ERROR(error);
}
uint64_t ob_frame_get_system_timestamp_us(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
void ob_frame_set_system_timestamp_us(ob_frame *frame, uint64_t system_timestamp_us, ob_error **error) {
    (void)frame; (void)system_timestamp_us; SAFE_ERROR(error);
}
uint64_t ob_frame_get_global_timestamp_us(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
uint8_t *ob_frame_get_data(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return nullptr;
}
void ob_frame_update_data(ob_frame *frame, const uint8_t *data, uint32_t data_size, ob_error **error) {
    (void)frame; (void)data; (void)data_size; SAFE_ERROR(error);
}
uint32_t ob_frame_get_data_size(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
uint8_t *ob_frame_get_metadata(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return nullptr;
}
uint32_t ob_frame_get_metadata_size(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
void ob_frame_update_metadata(ob_frame *frame, const uint8_t *metadata, uint32_t metadata_size, ob_error **error) {
    (void)frame; (void)metadata; (void)metadata_size; SAFE_ERROR(error);
}
bool ob_frame_has_metadata(const ob_frame *frame, ob_frame_metadata_type type, ob_error **error) {
    (void)frame; (void)type; SAFE_ERROR(error); return false;
}
int64_t ob_frame_get_metadata_value(const ob_frame *frame, ob_frame_metadata_type type, ob_error **error) {
    (void)frame; (void)type; SAFE_ERROR(error); return 0;
}
ob_stream_profile *ob_frame_get_stream_profile(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return nullptr;
}
void ob_frame_set_stream_profile(ob_frame *frame, const ob_stream_profile *stream_profile, ob_error **error) {
    (void)frame; (void)stream_profile; SAFE_ERROR(error);
}
ob_sensor *ob_frame_get_sensor(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return nullptr;
}
ob_device *ob_frame_get_device(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return nullptr;
}
uint32_t ob_video_frame_get_width(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
uint32_t ob_video_frame_get_height(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
ob_pixel_type ob_video_frame_get_pixel_type(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return static_cast<ob_pixel_type>(0);
}
void ob_video_frame_set_pixel_type(ob_frame *frame, ob_pixel_type pixel_type, ob_error **error) {
    (void)frame; (void)pixel_type; SAFE_ERROR(error);
}
uint8_t ob_video_frame_get_pixel_available_bit_size(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
void ob_video_frame_set_pixel_available_bit_size(ob_frame *frame, uint8_t bit_size, ob_error **error) {
    (void)frame; (void)bit_size; SAFE_ERROR(error);
}
float ob_depth_frame_get_value_scale(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0.0f;
}
void ob_depth_frame_set_value_scale(ob_frame *frame, float value_scale, ob_error **error) {
    (void)frame; (void)value_scale; SAFE_ERROR(error);
}
float ob_points_frame_get_coordinate_value_scale(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0.0f;
}
ob_accel_value ob_accel_frame_get_value(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error);
    ob_accel_value v = {};
    return v;
}
float ob_accel_frame_get_temperature(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0.0f;
}
ob_gyro_value ob_gyro_frame_get_value(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error);
    ob_gyro_value v = {};
    return v;
}
float ob_gyro_frame_get_temperature(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0.0f;
}
uint32_t ob_frameset_get_count(const ob_frame *frameset, ob_error **error) {
    (void)frameset; SAFE_ERROR(error); return 0;
}
ob_frame *ob_frameset_get_depth_frame(const ob_frame *frameset, ob_error **error) {
    (void)frameset; SAFE_ERROR(error); return nullptr;
}
ob_frame *ob_frameset_get_color_frame(const ob_frame *frameset, ob_error **error) {
    (void)frameset; SAFE_ERROR(error); return nullptr;
}
ob_frame *ob_frameset_get_ir_frame(const ob_frame *frameset, ob_error **error) {
    (void)frameset; SAFE_ERROR(error); return nullptr;
}
ob_frame *ob_frameset_get_points_frame(const ob_frame *frameset, ob_error **error) {
    (void)frameset; SAFE_ERROR(error); return nullptr;
}
ob_frame *ob_frameset_get_frame(const ob_frame *frameset, ob_frame_type frame_type, ob_error **error) {
    (void)frameset; (void)frame_type; SAFE_ERROR(error); return nullptr;
}
ob_frame *ob_frameset_get_frame_by_index(const ob_frame *frameset, uint32_t index, ob_error **error) {
    (void)frameset; (void)index; SAFE_ERROR(error); return nullptr;
}
void ob_frameset_push_frame(ob_frame *frameset, const ob_frame *frame, ob_error **error) {
    (void)frameset; (void)frame; SAFE_ERROR(error);
}
uint32_t ob_point_cloud_frame_get_width(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}
uint32_t ob_point_cloud_frame_get_height(const ob_frame *frame, ob_error **error) {
    (void)frame; SAFE_ERROR(error); return 0;
}

// ============================================================================
// RecordPlayback.h
// ============================================================================
ob_record_device *ob_create_record_device(ob_device *device, const char *file_path, bool compression_enabled, ob_error **error) {
    (void)device; (void)file_path; (void)compression_enabled; SAFE_ERROR(error); return &s_record_device;
}
void ob_delete_record_device(ob_record_device *recorder, ob_error **error) { (void)recorder; SAFE_ERROR(error); }
void ob_record_device_pause(ob_record_device *recorder, ob_error **error) { (void)recorder; SAFE_ERROR(error); }
void ob_record_device_resume(ob_record_device *recorder, ob_error **error) { (void)recorder; SAFE_ERROR(error); }
ob_device *ob_create_playback_device(const char *file_path, ob_error **error) {
    (void)file_path; SAFE_ERROR(error); return &s_device;
}
void ob_playback_device_pause(ob_device *player, ob_error **error) { (void)player; SAFE_ERROR(error); }
void ob_playback_device_resume(ob_device *player, ob_error **error) { (void)player; SAFE_ERROR(error); }
void ob_playback_device_seek(ob_device *player, const uint64_t timestamp, ob_error **error) {
    (void)player; (void)timestamp; SAFE_ERROR(error);
}
void ob_playback_device_set_playback_rate(ob_device *player, const float rate, ob_error **error) {
    (void)player; (void)rate; SAFE_ERROR(error);
}
ob_playback_status ob_playback_device_get_current_playback_status(ob_device *player, ob_error **error) {
    (void)player; SAFE_ERROR(error); return static_cast<ob_playback_status>(0);
}
void ob_playback_device_set_playback_status_changed_callback(ob_device *player, ob_playback_status_changed_callback callback, void *user_data,
                                                             ob_error **error) {
    (void)player; (void)callback; (void)user_data; SAFE_ERROR(error);
}
uint64_t ob_playback_device_get_position(ob_device *player, ob_error **error) {
    (void)player; SAFE_ERROR(error); return 0;
}
uint64_t ob_playback_device_get_duration(ob_device *player, ob_error **error) {
    (void)player; SAFE_ERROR(error); return 0;
}

// ============================================================================
// Utils.h
// ============================================================================
bool ob_transformation_3d_to_3d(const OBPoint3f source_point3f, OBExtrinsic extrinsic, OBPoint3f *target_point3f, ob_error **error) {
    (void)source_point3f; (void)extrinsic; (void)target_point3f; SAFE_ERROR(error); return false;
}
bool ob_transformation_2d_to_3d(const OBPoint2f source_point2f, const float source_depth_pixel_value, const OBCameraIntrinsic source_intrinsic,
                                OBExtrinsic extrinsic, OBPoint3f *target_point3f, ob_error **error) {
    (void)source_point2f; (void)source_depth_pixel_value; (void)source_intrinsic; (void)extrinsic; (void)target_point3f; SAFE_ERROR(error); return false;
}
bool ob_transformation_3d_to_2d(const OBPoint3f source_point3f, const OBCameraIntrinsic target_intrinsic, const OBCameraDistortion target_distortion,
                                OBExtrinsic extrinsic, OBPoint2f *target_point2f, ob_error **error) {
    (void)source_point3f; (void)target_intrinsic; (void)target_distortion; (void)extrinsic; (void)target_point2f; SAFE_ERROR(error); return false;
}
bool ob_transformation_2d_to_2d(const OBPoint2f source_point2f, const float source_depth_pixel_value, const OBCameraIntrinsic source_intrinsic,
                                const OBCameraDistortion source_distortion, const OBCameraIntrinsic target_intrinsic,
                                const OBCameraDistortion target_distortion, OBExtrinsic extrinsic, OBPoint2f *target_point2f, ob_error **error) {
    (void)source_point2f; (void)source_depth_pixel_value; (void)source_intrinsic; (void)source_distortion;
    (void)target_intrinsic; (void)target_distortion; (void)extrinsic; (void)target_point2f; SAFE_ERROR(error); return false;
}
ob_frame *transformation_depth_frame_to_color_camera(ob_device *device, ob_frame *depth_frame, uint32_t target_color_camera_width,
                                                     uint32_t target_color_camera_height, ob_error **error) {
    (void)device; (void)depth_frame; (void)target_color_camera_width; (void)target_color_camera_height; SAFE_ERROR(error); return nullptr;
}
bool transformation_init_xy_tables(const ob_calibration_param calibration_param, const ob_sensor_type sensor_type, float *data, uint32_t *data_size,
                                   ob_xy_tables *xy_tables, ob_error **error) {
    (void)calibration_param; (void)sensor_type; (void)data; (void)data_size; (void)xy_tables; SAFE_ERROR(error); return false;
}
void transformation_depth_to_pointcloud(ob_xy_tables *xy_tables, const void *depth_image_data, void *pointcloud_data, ob_error **error) {
    (void)xy_tables; (void)depth_image_data; (void)pointcloud_data; SAFE_ERROR(error);
}
void transformation_depth_to_rgbd_pointcloud(ob_xy_tables *xy_tables, const void *depth_image_data, const void *color_image_data,
                                             void *pointcloud_data, ob_error **error) {
    (void)xy_tables; (void)depth_image_data; (void)color_image_data; (void)pointcloud_data; SAFE_ERROR(error);
}
bool ob_calibration_3d_to_3d(const ob_calibration_param calibration_param, const ob_point3f source_point3f, const ob_sensor_type source_sensor_type,
                             const ob_sensor_type target_sensor_type, ob_point3f *target_point3f, ob_error **error) {
    (void)calibration_param; (void)source_point3f; (void)source_sensor_type; (void)target_sensor_type; (void)target_point3f; SAFE_ERROR(error); return false;
}
bool ob_calibration_2d_to_3d(const ob_calibration_param calibration_param, const ob_point2f source_point2f, const float source_depth_pixel_value,
                             const ob_sensor_type source_sensor_type, const ob_sensor_type target_sensor_type, ob_point3f *target_point3f,
                             ob_error **error) {
    (void)calibration_param; (void)source_point2f; (void)source_depth_pixel_value; (void)source_sensor_type; (void)target_sensor_type;
    (void)target_point3f; SAFE_ERROR(error); return false;
}
bool ob_calibration_3d_to_2d(const ob_calibration_param calibration_param, const ob_point3f source_point3f, const ob_sensor_type source_sensor_type,
                             const ob_sensor_type target_sensor_type, ob_point2f *target_point2f, ob_error **error) {
    (void)calibration_param; (void)source_point3f; (void)source_sensor_type; (void)target_sensor_type; (void)target_point2f; SAFE_ERROR(error); return false;
}
bool ob_calibration_2d_to_2d(const ob_calibration_param calibration_param, const ob_point2f source_point2f, const float source_depth_pixel_value,
                             const ob_sensor_type source_sensor_type, const ob_sensor_type target_sensor_type, ob_point2f *target_point2f,
                             ob_error **error) {
    (void)calibration_param; (void)source_point2f; (void)source_depth_pixel_value; (void)source_sensor_type; (void)target_sensor_type;
    (void)target_point2f; SAFE_ERROR(error); return false;
}
bool ob_save_pointcloud_to_ply(const char *file_name, ob_frame *frame, bool save_binary, bool use_mesh, float mesh_threshold, ob_error **error) {
    (void)file_name; (void)frame; (void)save_binary; (void)use_mesh; (void)mesh_threshold; SAFE_ERROR(error); return false;
}
bool ob_save_lidar_pointcloud_to_ply(const char *file_name, ob_frame *frame, bool save_binary, ob_error **error) {
    (void)file_name; (void)frame; (void)save_binary; SAFE_ERROR(error); return false;
}

// ============================================================================
// TypeHelper.h
// ============================================================================
const char *ob_format_type_to_string(OBFormat type) { (void)type; return "UNKNOWN"; }
const char *ob_frame_type_to_string(OBFrameType type) { (void)type; return "UNKNOWN"; }
const char *ob_stream_type_to_string(OBStreamType type) { (void)type; return "UNKNOWN"; }
const char *ob_sensor_type_to_string(OBSensorType type) { (void)type; return "UNKNOWN"; }
const char *ob_imu_rate_type_to_string(OBIMUSampleRate type) { (void)type; return "UNKNOWN"; }
const char *ob_gyro_range_type_to_string(OBGyroFullScaleRange type) { (void)type; return "UNKNOWN"; }
const char *ob_accel_range_type_to_string(OBAccelFullScaleRange type) { (void)type; return "UNKNOWN"; }
const char *ob_lidar_scan_rate_type_to_string(OBLiDARScanRate type) { (void)type; return "UNKNOWN"; }
const char *ob_meta_data_type_to_string(OBFrameMetadataType type) { (void)type; return "UNKNOWN"; }
OBStreamType ob_sensor_type_to_stream_type(OBSensorType type) { (void)type; return OB_STREAM_UNKNOWN; }
const char *ob_format_to_string(OBFormat format) { (void)format; return "UNKNOWN"; }

}  // extern "C"
