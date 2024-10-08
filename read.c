#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "McuSystemPb.pb.h"
#include "PreferenceProvider.pb.h"
#include <pb_encode.h>
#include <pb_decode.h>

enum channels {
    MSG_AP_TO_MAIN_TEST = 1,
    MSG_AT_CMD_FROM_MAIN_TO_MCU = 3,
    MSG_AT_RSP_FROM_MCU_TO_MAIN = 4,
    MSG_CONNECTION_PARAM = 1,
    MSG_HOST_ENABLE_ACTIVITY_STATUS_REPORT = 334,
    MSG = 360,
    MSG_HOST_BOOT_COMPLETE_NOMAL_MODE = 373, // PreferenceProvider.oppo_mcu_mode_t
    MSG_HOST_ENTER_POWEROFF_MODE = 374, // PreferenceProvider.oppo_mcu_mode_t
    MSG_HOST_ENTER_BAND_MODE = 375, // PreferenceProvider.oppo_mcu_mode_t
    MSG_HOST_CUR_WORK_MODE_REQUEST = 376,
    MSG_HOST_GET_CUR_HAND_MODE = 378,
    MSG_HOST_ANDROID_BOOT_NOTIFY = 386, // McuSystemPb.boot_notify
    MSG_HOST_ALGO_CMD = 503,
    MSG_HOST_FEEDBACK_TEST_TASK_A_REQUEST = 907,
    MSG_HOST_FEEDBACK_TEST_TASK_B_REQUEST = 909,
    MSG_HOST_FEEDBACK_TEST_TASK_C_REQUEST = 911,
    MSG_HOST_FS_UPLOAD_REQUEST = 915,
    MSG_HOST_FS_DATA_REPORT = 917,
    MSG_HOST_FS_DATA_RESPONSE = 918,
    MSG_HOST_FS_UPLOAD_RESPONSE = 916,
    MSG_HOST_GET_CUR_LANGUAGE = 381,
    MSG_HOST_GPS_DATA = 601,
    MSG_HOST_LOG_REQUEST = 101,
    MSG_HOST_MCU_SCREEN_ROTATION_RESPONSE = 366,
    MSG_HOST_MMI_ACC_CALIB_CMD = 815,
    MSG_HOST_MMI_ALGO_CMD = 827,
    MSG_HOST_MMI_BLE_CMD = 811,
    MSG_HOST_MMI_CAP_CALIB_CMD = 819,
    MSG_HOST_MMI_CURRENT_END_ID = 914,
    MSG_HOST_MMI_CURRENT_START_ID = 801,
    MSG_HOST_MMI_ECG_CMD = 805,
    MSG_HOST_MMI_FLASH_CMD = 809,
    MSG_HOST_MMI_GYRO_CALIB_CMD = 817,
    MSG_HOST_MMI_KEY_CMD = 825,
    MSG_HOST_MMI_LCD_CMD = 807,
    MSG_HOST_MMI_LIGHTSENSOR_CALI_CMD = 821,
    MSG_HOST_MMI_MOTOR_CMD = 823,
    MSG_HOST_MMI_PPG_CMD = 803,
    MSG_HOST_MMI_PRESSURE_CMD = 813,
    MSG_HOST_MMI_SENSOR_READ = 801,
    MSG_HOST_MMI_TP_CMD = 829,
    MSG_HOST_NOTIFY_CHARGE_STATUS = 482,
    MSG_HOST_NOTIFY_SCREEN_STATUS = 481,
    MSG_HOST_OOBE_FACTORY_TEST = 388,
    MSG_HOST_OOBE_NOTIFY = 384, // McuSystemPb.oobe_notify_t
    MSG_HOST_OTA_DOWNLOAD = 110,
    MSG_HOST_OTA_NOTAIFY = 521,
    MSG_HOST_PUSH_ACTIVITY_TOTAL_DATA = 330,
    MSG_HOST_READ_BLE_MAC_ADDRESS = 473,
    MSG_HOST_REQUEST_ACTIVITY_HIS_DATA = 324,
    MSG_HOST_REQUEST_ACTIVITY_HIS_SYNC = 322,
    MSG_HOST_REQUEST_ACTIVITY_REALTIME_DATA = 320, //empty
    MSG_HOST_REQUEST_ACTIVITY_SWITCH = 329,
    MSG_HOST_REQUEST_CALIBRATION_PARAM = 420,
    MSG_HOST_REQUEST_CLEAR_APP = 391,
    MSG_HOST_REQUEST_FACTORY_RESET = 115,
    MSG_HOST_REQUEST_GET_WORKMODE_SWITCH = 493,
    MSG_HOST_REQUEST_HEARTRATE_CURCTRL = 431, // HeartRate.HeartRateRequest
    MSG_HOST_REQUEST_HEARTRATE_HISCTRL = 433,
    MSG_HOST_REQUEST_HEARTRATE_HIS_DATA = 436,
    MSG_HOST_REQUEST_HEARTRATE_HIS_SYNC = 434,
    MSG_HOST_REQUEST_LIFT_WRIST_SWITCH_STATUS = 411,
    MSG_HOST_REQUEST_MCU_REBOOT_REASON = 395, // empty
    MSG_HOST_REQUEST_MCU_SCREEN_ROTATION = 365,
    MSG_HOST_REQUEST_MCU_VERSION = 361,
    MSG_HOST_REQUEST_MOTOR_CALI = 511,
    MSG_HOST_REQUEST_OFF_WRIST_STATUS = 408,
    MSG_HOST_REQUEST_OFF_WRIST_SWITCH_STATUS = 406,
    MSG_HOST_REQUEST_SET_WORKMODE_SWITCH = 491,
    MSG_HOST_REQUEST_SLEEP_HIS_DATA = 483,
    MSG_HOST_REQUEST_SLEEP_HIS_SYNC = 481,
    MSG_HOST_REQUEST_SLEEP_STATE = 486,
    MSG_HOST_REQUEST_SPORTS_PRESS_BEGIN = 345,
    MSG_HOST_REQUEST_SPORTS_PRESS_PAUSE = 347,
    MSG_HOST_REQUEST_SPORTS_PRESS_RESUME = 348,
    MSG_HOST_REQUEST_SPORTS_PRESS_STOP = 346,
    MSG_HOST_REQUEST_STEPS_HIS_SYNC = 301,
    MSG_HOST_REQUEST_STEP_HIS_DATA = 303,
    MSG_HOST_REQUEST_WRITE_APP = 389,
    MSG_HOST_RESET_SENSORHUB = 117,
    MSG_HOST_SENSOR_TUNNEL = 501,
    MSG_HOST_SET_AUTO_BACKLIGHT_SWITCH = 401,
    MSG_HOST_SET_HAND_MODE = 380,
    MSG_HOST_SET_LANGUAGE = 383, // McuSystemPb.band_language_t
    MSG_HOST_SET_LIFT_WRIST_SWITCH = 409,
    MSG_HOST_SET_MCU_SCREEN_ROTATION = 367,
    MSG_HOST_SET_OFF_WRIST_SWITCH = 404,
    MSG_HOST_SET_PHY_FITNESS_PARAM = 354,
    MSG_HOST_SINGLE_WRITE_TEST_SEND = 902,
    MSG_HOST_SPORT_CONTROL_CMD = 306,
    MSG_HOST_SPORT_PARAM_CONFIG = 307,
    MSG_HOST_START_SINGLE_READ_TEST = 904,
    MSG_HOST_START_SINGLE_WRITE_TEST = 901,
    MSG_HOST_UPDATE_USERPROFILE_INFO = 372, // PreferenceProvider.PreferenceBody
    MSG_HOST_WRITE_BLE_MAC_ADDRESS = 471,
    MSG_TYPES = 999,
    MSG_MAIN_TO_AP_TEST = 2,
    MSG_MCU_ACTIVITY_DATA_RESPONSE = 321,
    MSG_MCU_ACTIVITY_HIS_DATA_RESPONSE = 325,
    MSG_MCU_ACTIVITY_HIS_FIRST_RESPONSE = 323,
    MSG_MCU_ACTIVITY_STATUS_REPORT = 333,
    MSG_MCU_ANDROID_BOOT_NOTIFY_RESPONSE = 387, // waitForMcuModeResponse
    MSG_MCU_AUTO_BACKLIGHT_UPDATE = 402,
    MSG_MCU_AUTO_CALORIES_AIM_COMPLETE = 326,
    MSG_MCU_AUTO_DISTANCE_AIM_COMPLETE = 327,
    MSG_MCU_AUTO_EXERCISE_AIM_COMPLETE = 328,
    MSG_MCU_BLE_MAC_ADDRESS_RESPONSE = 474,
    MSG_MCU_CLEAR_APP_ACK = 392,
    MSG_MCU_CUR_WORK_MODE_RESPONE = 377, // PreferenceProvider.oppo_mcu_work_mode_response_t
    MSG_MCU_FACTORY_RESET_RESPONSE = 116,
    MSG_MCU_FEEDBACK_TEST_TASK_A_ACK = 908,
    MSG_MCU_FEEDBACK_TEST_TASK_B_ACK = 910,
    MSG_MCU_FEEDBACK_TEST_TASK_C_ACK = 912,
    MSG_MCU_GET_WORKMODE_SWITCH_RESPONSE = 494,
    MSG_MCU_GMT_CHANGED_DATA_SYNC = 423,
    MSG_MCU_GPS_DATA = 602,
    MSG_MCU_GPS_STATUS_DATA = 604,
    MSG_MCU_HEARTRATE_HIS_DATA_RESPONSE = 437,
    MSG_MCU_HEARTRATE_HIS_FIRST_RESPONES = 435,
    MSG_MCU_HEARTRATE_QUIET_DATA_RESPONESE = 438,
    MSG_MCU_HEATRATE_CURDATA_RESPONESE = 432,
    MSG_MCU_LIFT_WRIST_STATUS_UPDATE = 410,
    MSG_MCU_LIFT_WRIST_SWITCH_STATUS_RESPONSE = 412,
    MSG_MCU_LOG_RESPONSE = 102,
    MSG_MCU_MMI_ACC_CALIB_RESPONSE = 816,
    MSG_MCU_MMI_ALGO_RESPONSE = 828,
    MSG_MCU_MMI_BLE_RESPONSE = 812,
    MSG_MCU_MMI_CAP_CALIB_RESPONSE = 820,
    MSG_MCU_MMI_ECG_RSP = 806,
    MSG_MCU_MMI_FLASH_RESPONSE = 810,
    MSG_MCU_MMI_GYRO_CALIB_RESPONSE = 818,
    MSG_MCU_MMI_KEY_RESPONSE = 826,
    MSG_MCU_MMI_LCD_RESPONSE = 808,
    MSG_MCU_MMI_LIGHTSENSOR_CALI_RESPONSE = 822,
    MSG_MCU_MMI_MOTOR_RESPONSE = 824,
    MSG_MCU_MMI_PPG_RSP = 804,
    MSG_MCU_MMI_PRESSURE_RESPONSE = 814,
    MSG_MCU_MMI_SENSOR_RESPONSE = 802,
    MSG_MCU_MMI_TP_RESPONSE = 830,
    MSG_MCU_MOTOR_CALI_RESPONSE = 512,
    MSG_MCU_OFF_WRIST_STATUS_UPDATE = 405,
    MSG_MCU_OFF_WRIST_SWITCH_STATUS_RESPONSE = 407,
    MSG_MCU_OOBE_RESPONSE = 385,
    MSG_MCU_OTA_NOTAIFY_ACK = 522,
    MSG_MCU_READ_MCU_VERSION_RESPONE = 362,
    MSG_MCU_REBOOT_REASON_RESPONSE = 396, // McuSystemPb.reboot_reason
    MSG_MCU_REQUEST_ACTIVITY_TOTAL_DATA = 331,
    MSG_MCU_REQUEST_BATTERY_INFO = 397,
    MSG_MCU_RESET_SENSORHUB_RESPONSE = 118,
    MSG_MCU_RESPONSE_CALIBRATION_PARAM = 421,
    MSG_MCU_RESPONSE_CUR_HAND_MODE = 379, // empty
    MSG_MCU_RESPONSE_CUR_LANGUAGE = 382,
    MSG_MCU_RESPONSE_CUR_SLEEP_STATE = 487,
    MSG_MCU_RESPONSE_READ_SYSTEM_TIME = 426,
    MSG_MCU_RESPONSE_UPDATE_SYS_TIME = 424,
    MSG_MCU_SEDENTERY_RESPONSE = 311,
    MSG_MCU_SENSOR_TUNNEL = 502,
    MSG_MCU_SET_BLE_MAC_RESPONSE = 472,
    MSG_MCU_SET_WORKMODE_SWITCH_RESPONSE = 492,
    MSG_MCU_SINGLE_READ_TEST_DATA = 906,
    MSG_MCU_SINGLE_WRITE_TEST_RESULT = 903,
    MSG_MCU_SLEEP_HIS_DATA_RESPONSE = 484,
    MSG_MCU_SLEEP_HIS_FIRST_RESPONSE = 482,
    MSG_MCU_SLEEP_STATUS_UPDATE = 485,
    MSG_MCU_SPORTS_DETAIL_RESPONSE = 342,
    MSG_MCU_SPORTS_GPS_POINT_RESPONSE = 350,
    MSG_MCU_SPORTS_REALTIME_RESPONSE = 341,
    MSG_MCU_SPORTS_REMIND_RESPONSE = 343,
    MSG_MCU_SPORTS_RESULT_RESPONSE = 344,
    MSG_MCU_SPORTS_SWIMMING_PARAM_RESPONSE = 349,
    MSG_MCU_SPORT_PROMPT_DATA = 309,
    MSG_MCU_SPORT_REAL_TIME_DATA = 308,
    MSG_MCU_START_SINGLE_READ_TEST = 905,
    MSG_MCU_STEPAIM_UPDATES = 305,
    MSG_MCU_STEPS_HIS_DATA_RESPONSE = 304,
    MSG_MCU_STEPS_HIS_FIRST_RESPONSE = 302,
    MSG_MCU_WAKEUP_HOST_SYNC_ACTIVITY_TOTAL = 332,
    MSG_MCU_WRITE_APP_ACK = 390,
    MSG_OTA_MCU_UPLOAD = 100,
    MSG_SPORTS_NOTIFY_PER_KILOMETER = 352,
    MSG_SPORTS_STORAGE_WRITE_CROSS = 351,
    MSG_SPORTS_TEST_SPI = 353,

    MSG_WRIST_BAND_RESPONE = 388,
    MSG_MCU_RESPONSE_ACTIVITY_DATA = 337, // timestamp (part of protobuf), bytearray uint32_t [calories, distance, height, exercise, type, steps]
};

void send_message(int fd, int channel, int len, uint8_t *buf) {
    uint8_t b[4004];
    ((uint16_t*)b)[0] = channel;
    ((uint16_t*)b)[1] = len;
    memcpy(b + 4, buf, len);
    write(fd, b, len + 4);

    printf("TX: %d // ", channel);
    for(int i=0; i<(len + 4); i++)
        printf("%02hhx:", b[i]);
    printf("\n");
}

int main() {
    int fd = open("/dev/dcc_data", O_RDWR);
    uint8_t buf[4004];
    while(1) {
        int n = read(fd, buf, sizeof(buf));
        int channel = ((uint16_t*)buf)[0];
        int len = ((uint16_t*)buf)[1];
        if ((n-4) != len) printf("!!");
        printf("RX: %d // ", channel);
        for(int i=0; i<n; i++)
            printf("%02hhx:", buf[i]);
        printf("\n");

        if (channel == MSG_MCU_REBOOT_REASON_RESPONSE) {
            McuSystemPb_reboot_reason message = McuSystemPb_reboot_reason_init_zero;
            pb_istream_t stream = pb_istream_from_buffer(buf + 4, len);
            int status = pb_decode(&stream, McuSystemPb_reboot_reason_fields, &message);
            printf("Protobuf decode returned %d, reason %d/%d, eStatus %d/%d\n",
                    status,
                    message.has_reason, message.reason,
                    message.has_eStatus, message.eStatus);
            if (message.has_mcuSysTime) {
                printf("...mcuSysTime timesource %d, type %d, time %d, timezone %d\n",
                        message.mcuSysTime.timeSource,
                        message.mcuSysTime.type,
                        message.mcuSysTime.time,
                        message.mcuSysTime.timezone);
            }
            // McuSystemPb.reboot_reason
            send_message(fd, MSG_HOST_REQUEST_MCU_REBOOT_REASON, 0, buf);
            sleep(1);
            send_message(fd, MSG_HOST_REQUEST_CALIBRATION_PARAM, 0, buf);
        }
        if (channel == MSG_MCU_RESPONSE_CALIBRATION_PARAM) {
            McuSystemPb_light_cali_rsp_t message = McuSystemPb_light_cali_rsp_t_init_zero;
            pb_istream_t stream = pb_istream_from_buffer(buf + 4, len);
            int status = pb_decode(&stream, McuSystemPb_light_cali_rsp_t_fields, &message);
            printf("Received light calibration response %d red_max_lux %d, green_max_lux %d, blue_max_lux %d, white_max_lux %d, cail_coe: %f\n",
                    status,
                    message.red_max_lux,
                    message.green_max_lux,
                    message.blue_max_lux,
                    message.white_max_lux,
                    message.cail_coe);

            McuSystemPb_boot_notify boot_notify_message = McuSystemPb_boot_notify_init_zero;
            boot_notify_message.has_type = 1;
            boot_notify_message.type = 2;

            boot_notify_message.has_oobe = 1;
            boot_notify_message.oobe.has_oobeStatus = 1;
            boot_notify_message.oobe.oobeStatus = 1;
            boot_notify_message.oobe.has_needUpdateWeather = 1;
            boot_notify_message.oobe.needUpdateWeather = 0;
            // notifyMcuBootComplete / makeUpSystemTimePb
            boot_notify_message.has_sysTime = 1;
            boot_notify_message.sysTime.time = time(NULL);;
            boot_notify_message.sysTime.oldTime = 0;
            boot_notify_message.sysTime.timezone = 60; // GMT+1
            boot_notify_message.sysTime.oldTimezone = 60; // GMT+1
            boot_notify_message.sysTime.type = 0;
            pb_ostream_t ostream = pb_ostream_from_buffer(buf, sizeof(buf));
            status = pb_encode(&ostream, McuSystemPb_boot_notify_fields, &boot_notify_message);
            printf("Serializing boot_notify returned %d %d\n", status, ostream.bytes_written);

            send_message(fd, MSG_HOST_ANDROID_BOOT_NOTIFY, ostream.bytes_written, buf);
        }
        if (channel == MSG_MCU_CUR_WORK_MODE_RESPONE) {
            PreferenceProvider_OppoMcuWorkModeResponseT message = PreferenceProvider_OppoMcuWorkModeResponseT_init_zero;
            pb_istream_t stream = pb_istream_from_buffer(buf + 4, len);
            int status = pb_decode(&stream, PreferenceProvider_OppoMcuWorkModeResponseT_fields, &message);
            printf("Received mcu work mode %d - %d/%d, lightCali %d(red %d), lastMode %d/%d, rebootReason %d/%d, type %d/%d\n",
                    status,
                    1, message.mode,
                    message.has_lightCali, message.lightCali.red_max_lux,
                    1, message.lastMode,
                    1, message.rebootReason,
                    1, message.type);
        }
        if (channel == MSG_MCU_OFF_WRIST_STATUS_UPDATE) {
            PreferenceProvider_OWStatus message = PreferenceProvider_OWStatus_init_zero;
            pb_istream_t stream = pb_istream_from_buffer(buf + 4, len);
            int status = pb_decode(&stream, PreferenceProvider_OWStatus_fields, &message);
            printf("Received off-wrist status update %d -- %d/%d\n",
                    status,
                    message.has_status, message.status);
#if 0
            // We receive after like one minute an off-wrist status update without a status, use that to trigger an event later
            if (!message.has_status) {
                PreferenceProvider_OppoMcuModeT m = PreferenceProvider_OppoMcuModeT_init_zero;
                m.mode = 1; // 1 = manual, 2 = confirm, 3 = timeout, 4 = other
                m.type = 1; // 0 = android, 1 = wrist-band, 2 = off
                m.has_sysTime = 1;
                m.sysTime.time = time(NULL);;
                m.sysTime.oldTime = 0;
                m.sysTime.timezone = 60; // GMT+1
                m.sysTime.oldTimezone = 60; // GMT+1
                m.sysTime.type = 0;
                pb_ostream_t ostream = pb_ostream_from_buffer(buf, sizeof(buf));
                status = pb_encode(&ostream, PreferenceProvider_OppoMcuModeT_fields, &m);
                printf("Serializing oppomcumode %d %d\n", status, ostream.bytes_written);

                send_message(fd, MSG_HOST_ENTER_BAND_MODE, ostream.bytes_written, buf);
            }
#endif
        }
        if (channel == MSG_WRIST_BAND_RESPONE) {
            printf("Received wrist band mode response\n");
        }
        if (channel == MSG_MCU_RESPONSE_ACTIVITY_DATA) {
            printf("Received activity data\n");
        }
    }
}
