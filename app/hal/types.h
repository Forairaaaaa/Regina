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

/* -------------------------------------------------------------------------- */
/*                               Gamepad button                               */
/* -------------------------------------------------------------------------- */
namespace GAMEPAD
{
    enum GamePadButton_t
    {
        BTN_START = 0,
        BTN_SELECT,
        BTN_UP,
        BTN_LEFT,
        BTN_RIGHT,
        BTN_DOWN,
        BTN_X,
        BTN_Y,
        BTN_A,
        BTN_B,
        BTN_LEFT_STICK,
        GAMEPAD_BUTTON_NUM,
    };
} // namespace GAMEPAD

/* -------------------------------------------------------------------------- */
/*                                     IMU                                    */
/* -------------------------------------------------------------------------- */
namespace IMU
{
    struct ImuData_t
    {
        float accelX;
        float accelY;
        float accelZ;
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
        uint8_t brightness = 255;
        uint8_t orientation = 0;
        std::string wifiSsid = "";
        std::string wifiPassword = "";
        bool beepOn = true;
        bool reverseEncoder = false;
        LocaleCode_t localeCode = locale_code_en;
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
/*                                    MISC                                    */
/* -------------------------------------------------------------------------- */
typedef std::function<void(const std::string& log, bool pushScreen, bool clear)> OnLogPageRenderCallback_t;

#define APP_VERSION "V1.0.0"
