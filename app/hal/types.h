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

/* -------------------------------------------------------------------------- */
/*                                   Console                                  */
/* -------------------------------------------------------------------------- */
namespace CONSOLE
{
    class ConsolePipe_t : public SmoothUIToolKit::RingBuffer<char, 124>
    {
    public:
        template <typename... Args>
        void log(const char* msg, const Args&... args)
        {
            // std::string formatted_msg = fmt::format(msg, args...);
            // Gcc sucks
            auto format_args = fmt::make_format_args(args...);
            std::string formatted_msg = fmt::vformat(msg, format_args);

            // New line
            if (!this->isEmpty())
                this->put('\n');

            for (const auto& i : formatted_msg)
            {
                this->put(i);
            }
        }
    };
} // namespace CONSOLE
