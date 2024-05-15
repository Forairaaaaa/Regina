/**
 * @file types.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-11
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
#include <M5GFX.h>
#include "../hal/utils/lgfx_fx/lgfx_fx.h"
#include <queue>

/* -------------------------------------------------------------------------- */
/*                                    Power                                   */
/* -------------------------------------------------------------------------- */
namespace POWER
{
    enum PowerState_t
    {
        state_awake = 0,
        state_going_sleep,
        state_ready_to_sleep,
        state_sleeping,
    };
} // namespace POWER

/* -------------------------------------------------------------------------- */
/*                                   Console                                  */
/* -------------------------------------------------------------------------- */
namespace CONSOLE
{
    class ConsolePipe_t : public SmoothUIToolKit::RingBuffer<char, 124>
    {
    private:
        bool _auto_newline;
        bool _is_enable;

    public:
        ConsolePipe_t() : _auto_newline(false), _is_enable(true) {}

        void setAutoNewLine(bool autoNewLine) { _auto_newline = autoNewLine; }

        void setEnable(bool isEnable) { _is_enable = isEnable; }

        template <typename... Args>
        void log(const char* msg, const Args&... args)
        {
            if (!_is_enable)
                return;

            // std::string formatted_msg = fmt::format(msg, args...);
            // Gcc sucks
            auto format_args = fmt::make_format_args(args...);
            std::string formatted_msg = fmt::vformat(msg, format_args);

            // New line
            if (_auto_newline)
                this->put('\n');

            for (const auto& i : formatted_msg)
            {
                this->put(i);
            }
        }
    };
} // namespace CONSOLE

namespace NOTIF
{
    struct Notification_t
    {
        std::string title;
        std::string msg;

        Notification_t() = default;
        Notification_t(const std::string& title, const std::string& msg)
        {
            this->title = title;
            this->msg = msg;
        }
    };
}; // namespace NOTIF

/* -------------------------------------------------------------------------- */
/*                                    Misc                                    */
/* -------------------------------------------------------------------------- */
#define APP_VERSION "V1.0.0"

namespace SHARED_DATA
{
    struct SharedData_t
    {
        LGFX_SpriteFx* console_canvas = nullptr;
        CONSOLE::ConsolePipe_t console_msg_pipe;

        POWER::PowerState_t power_state = POWER::state_awake;
        uint32_t awake_time_count = 0;

        std::queue<NOTIF::Notification_t> notification_pipe;
    };
} // namespace SHARED_DATA
