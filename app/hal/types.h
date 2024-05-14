/**
 * @file types.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>
#include <string>
#include <functional>
#include <smooth_ui_toolkit.h>
#include <mooncake.h>
#include <spdlog/fmt/bundled/format.h>

/* -------------------------------------------------------------------------- */
/*                               Gamepad button                               */
/* -------------------------------------------------------------------------- */
namespace GAMEPAD
{
    enum GamePadButton_t
    {
        BTN_A = 0,
        BTN_B,
        BTN_C,
        BTN_D,
        BTN_PWR,
        GAMEPAD_BUTTON_NUM
    };
} // namespace GAMEPAD

/* -------------------------------------------------------------------------- */
/*                                    Dials                                   */
/* -------------------------------------------------------------------------- */
namespace DIAL
{
    enum DialId_t
    {
        DIAL_A = 0,
        DIAL_B,
        DIAL_NUM,
    };
}

/* -------------------------------------------------------------------------- */
/*                                     IMU                                    */
/* -------------------------------------------------------------------------- */
namespace IMU
{
    struct Imu3D_t
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct ImuData_t
    {
        Imu3D_t accel;
        Imu3D_t gyro;
        Imu3D_t mag;
    };
} // namespace IMU

/* -------------------------------------------------------------------------- */
/*                                  Touchpad                                  */
/* -------------------------------------------------------------------------- */
namespace TOUCH
{
    /**
     * @brief Touch point
     *
     */
    struct Point_t
    {
        int x;
        int y;
    };
} // namespace TOUCH

/* -------------------------------------------------------------------------- */
/*                                 Locale code                                */
/* -------------------------------------------------------------------------- */
enum LocaleCode_t
{
    locale_code_en = 0,
    locale_code_cn,
    locale_code_jp,
};

/* -------------------------------------------------------------------------- */
/*                                System config                               */
/* -------------------------------------------------------------------------- */
namespace CONFIG
{
    // Default config
    struct SystemConfig_t
    {
        bool mute = false;
        bool dialAPinSwaped = false;
        bool dialBPinSwaped = false;
        std::string wifiSsid = "";
        std::string wifiPassword = "";
        uint32_t autoSleepTimeout = 12000;
    };
} // namespace CONFIG

/* -------------------------------------------------------------------------- */
/*                                  OTA info                                  */
/* -------------------------------------------------------------------------- */
namespace OTA_UPGRADE
{
    struct OtaInfo_t
    {
        bool upgradeAvailable = false;
        bool getInfoFailed = false;
        std::string latestVersion;
        std::string firmwareUrl;
    };
}; // namespace OTA_UPGRADE

/* -------------------------------------------------------------------------- */
/*                                Ble keyboard                                */
/* -------------------------------------------------------------------------- */
// https://github.com/T-vK/ESP32-BLE-Keyboard/blob/master/BleKeyboard.h
const uint8_t KEY_LEFT_CTRL = 0x80;
const uint8_t KEY_LEFT_SHIFT = 0x81;
const uint8_t KEY_LEFT_ALT = 0x82;
const uint8_t KEY_LEFT_GUI = 0x83;
const uint8_t KEY_RIGHT_CTRL = 0x84;
const uint8_t KEY_RIGHT_SHIFT = 0x85;
const uint8_t KEY_RIGHT_ALT = 0x86;
const uint8_t KEY_RIGHT_GUI = 0x87;

const uint8_t KEY_UP_ARROW = 0xDA;
const uint8_t KEY_DOWN_ARROW = 0xD9;
const uint8_t KEY_LEFT_ARROW = 0xD8;
const uint8_t KEY_RIGHT_ARROW = 0xD7;
const uint8_t KEY_BACKSPACE = 0xB2;
const uint8_t KEY_TAB = 0xB3;
const uint8_t KEY_RETURN = 0xB0;
const uint8_t KEY_ESC = 0xB1;
const uint8_t KEY_INSERT = 0xD1;
const uint8_t KEY_PRTSC = 0xCE;
const uint8_t KEY_DELETE = 0xD4;
const uint8_t KEY_PAGE_UP = 0xD3;
const uint8_t KEY_PAGE_DOWN = 0xD6;
const uint8_t KEY_HOME = 0xD2;
const uint8_t KEY_END = 0xD5;
const uint8_t KEY_CAPS_LOCK = 0xC1;
const uint8_t KEY_F1 = 0xC2;
const uint8_t KEY_F2 = 0xC3;
const uint8_t KEY_F3 = 0xC4;
const uint8_t KEY_F4 = 0xC5;
const uint8_t KEY_F5 = 0xC6;
const uint8_t KEY_F6 = 0xC7;
const uint8_t KEY_F7 = 0xC8;
const uint8_t KEY_F8 = 0xC9;
const uint8_t KEY_F9 = 0xCA;
const uint8_t KEY_F10 = 0xCB;
const uint8_t KEY_F11 = 0xCC;
const uint8_t KEY_F12 = 0xCD;
const uint8_t KEY_F13 = 0xF0;
const uint8_t KEY_F14 = 0xF1;
const uint8_t KEY_F15 = 0xF2;
const uint8_t KEY_F16 = 0xF3;
const uint8_t KEY_F17 = 0xF4;
const uint8_t KEY_F18 = 0xF5;
const uint8_t KEY_F19 = 0xF6;
const uint8_t KEY_F20 = 0xF7;
const uint8_t KEY_F21 = 0xF8;
const uint8_t KEY_F22 = 0xF9;
const uint8_t KEY_F23 = 0xFA;
const uint8_t KEY_F24 = 0xFB;

const uint8_t KEY_NUM_0 = 0xEA;
const uint8_t KEY_NUM_1 = 0xE1;
const uint8_t KEY_NUM_2 = 0xE2;
const uint8_t KEY_NUM_3 = 0xE3;
const uint8_t KEY_NUM_4 = 0xE4;
const uint8_t KEY_NUM_5 = 0xE5;
const uint8_t KEY_NUM_6 = 0xE6;
const uint8_t KEY_NUM_7 = 0xE7;
const uint8_t KEY_NUM_8 = 0xE8;
const uint8_t KEY_NUM_9 = 0xE9;
const uint8_t KEY_NUM_SLASH = 0xDC;
const uint8_t KEY_NUM_ASTERISK = 0xDD;
const uint8_t KEY_NUM_MINUS = 0xDE;
const uint8_t KEY_NUM_PLUS = 0xDF;
const uint8_t KEY_NUM_ENTER = 0xE0;
const uint8_t KEY_NUM_PERIOD = 0xEB;

typedef uint8_t MediaKeyReport[2];

const MediaKeyReport KEY_MEDIA_NEXT_TRACK = {1, 0};
const MediaKeyReport KEY_MEDIA_PREVIOUS_TRACK = {2, 0};
const MediaKeyReport KEY_MEDIA_STOP = {4, 0};
const MediaKeyReport KEY_MEDIA_PLAY_PAUSE = {8, 0};
const MediaKeyReport KEY_MEDIA_MUTE = {16, 0};
const MediaKeyReport KEY_MEDIA_VOLUME_UP = {32, 0};
const MediaKeyReport KEY_MEDIA_VOLUME_DOWN = {64, 0};
const MediaKeyReport KEY_MEDIA_WWW_HOME = {128, 0};
const MediaKeyReport KEY_MEDIA_LOCAL_MACHINE_BROWSER = {0, 1}; // Opens "My Computer" on Windows
const MediaKeyReport KEY_MEDIA_CALCULATOR = {0, 2};
const MediaKeyReport KEY_MEDIA_WWW_BOOKMARKS = {0, 4};
const MediaKeyReport KEY_MEDIA_WWW_SEARCH = {0, 8};
const MediaKeyReport KEY_MEDIA_WWW_STOP = {0, 16};
const MediaKeyReport KEY_MEDIA_WWW_BACK = {0, 32};
const MediaKeyReport KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION = {0, 64}; // Media Selection
const MediaKeyReport KEY_MEDIA_EMAIL_READER = {0, 128};

/* -------------------------------------------------------------------------- */
/*                                    MISC                                    */
/* -------------------------------------------------------------------------- */
typedef std::function<void(const std::string& log, bool pushScreen, bool clear)> OnLogPageRenderCallback_t;
