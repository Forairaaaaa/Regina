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

static constexpr int _panel_x = 2;
static constexpr int _panel_y = 49;
static constexpr int _panel_w = 40;
static constexpr int _panel_h = 13;
static constexpr int _panel_r = 4;

void WidgetClock::_reset_anim()
{
    constexpr int delay = 360;

    _data.shape_trans.jumpTo((HAL::GetCanvas()->width() - 24) / 2 - 24, HAL::GetCanvas()->height(), 24, 20);
    _data.shape_trans.moveTo(_panel_x, _panel_y, _panel_w, _panel_h);

    _data.shape_trans.setDelay(delay);
    _data.shape_trans.setDuration(500);
    // _data.shape_trans.setTransitionPath(EasingPath::easeOutBack);

    _data.shape_trans.getYTransition().setDuration(300);
    _data.shape_trans.getXTransition().setDelay(delay + 70);
    _data.shape_trans.getWTransition().setDelay(delay + 70);
    _data.shape_trans.getHTransition().setDelay(delay + 70);

    _data.update_time_count = 0;
    _data.colon_type = true;
}

void WidgetClock::onInit() { _reset_anim(); }

void WidgetClock::onUpdate()
{
    _data.shape_trans.update(HAL::Millis());

    // Update time
    if (HAL::Millis() - _data.update_time_count > _data.update_interval)
    {
        // Colon
        if (_data.shape_trans.isFinish())
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
    auto frame = _data.shape_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    // Time
    HAL::GetCanvas()->setTextColor(TFT_WHITE);
    HAL::GetCanvas()->setTextDatum(middle_center);
    HAL::GetCanvas()->setTextSize(1);
    HAL::GetCanvas()->drawString(_data.time.c_str(), frame.x + frame.w / 2, frame.y + frame.h / 2 + 1);
}
