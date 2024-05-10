/**
 * @file clock.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "widgets.h"
#include "../../../../assets/assets.h"
#include "hal/hal.h"
#include <mooncake.h>
#include <smooth_ui_toolkit.h>

using namespace SmoothUIToolKit;

static constexpr int _panel_startup_x = (128 - 24) / 2 - 24;
static constexpr int _panel_startup_y = 64 + 12;
static constexpr int _panel_startup_w = 24;
static constexpr int _panel_startup_h = 20;
static constexpr int _panel_x = 2;
static constexpr int _panel_y = 49;
static constexpr int _panel_w = 40;
static constexpr int _panel_h = 13;
static constexpr int _panel_r = 4;

void WidgetClock::onPopOut()
{
    constexpr int delay = 360;

    getTransition().jumpTo(_panel_startup_x, _panel_startup_y, _panel_startup_w, _panel_startup_h);
    getTransition().moveTo(_panel_x, _panel_y, _panel_w, _panel_h);

    getTransition().setEachDelay(delay + 70, delay + 70, delay, delay + 70);
    getTransition().setEachDuration(500, 300, 500, 500);

    _data.update_time_count = 0;
    _data.colon_type = true;
}

void WidgetClock::onHide()
{
    constexpr int delay = 60;

    getTransition().jumpTo(_panel_x, _panel_y, _panel_w, _panel_h);
    getTransition().moveTo(_panel_startup_x, _panel_startup_y, _panel_startup_w, _panel_startup_h);

    getTransition().setEachDelay(delay, delay, delay + 70, delay);
    getTransition().setEachDuration(300, 500, 300, 300);
}

void WidgetClock::onUpdate()
{
    // Update time
    if (HAL::Millis() - _data.update_time_count > _data.update_interval)
    {
        // Colon
        if (isPoppedOut())
            _data.colon_type = !_data.colon_type;

        // Time
        auto time = HAL::GetLocalTime();
        _data.time = fmt::format("{:02d}{}{:02d}", time->tm_hour, _data.colon_type ? ":" : " ", time->tm_min);
        // spdlog::info("{}", _data.time);

        _data.update_time_count = HAL::Millis();
    }

    // _data.time = "22:33";
}

void WidgetClock::onRender()
{
    // Panel
    auto frame = getTransition().getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    // Time
    HAL::GetCanvas()->setTextColor(TFT_WHITE);
    HAL::GetCanvas()->setTextDatum(middle_center);
    HAL::GetCanvas()->setTextSize(1);
    HAL::GetCanvas()->drawString(_data.time.c_str(), frame.x + frame.w / 2, frame.y + frame.h / 2 + 1);
}
