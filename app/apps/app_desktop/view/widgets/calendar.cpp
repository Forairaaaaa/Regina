/**
 * @file calendar.cpp
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

static constexpr int _panel_x = 44;
static constexpr int _panel_y = 49;
static constexpr int _panel_w = 82;
static constexpr int _panel_h = 13;
static constexpr int _panel_r = 4;

void WidgetCalendar::onPopOut()
{
    constexpr int delay = 400;

    _data.shape_trans.jumpTo((HAL::GetCanvas()->width() - 24) / 2 + 48, HAL::GetCanvas()->height(), 24, 20);
    _data.shape_trans.moveTo(_panel_x, _panel_y, _panel_w, _panel_h);

    _data.shape_trans.setDelay(delay);
    _data.shape_trans.setDuration(400);
    // _data.shape_trans.setTransitionPath(EasingPath::easeOutBack);

    _data.shape_trans.getYTransition().setDuration(300);
    _data.shape_trans.getXTransition().setDelay(delay + 70);
    _data.shape_trans.getWTransition().setDelay(delay + 70);
    _data.shape_trans.getHTransition().setDelay(delay + 70);

    _data.update_time_count = 0;
}

void WidgetCalendar::onUpdate()
{
    _data.shape_trans.update(HAL::Millis());

    if (HAL::Millis() - _data.update_time_count > _data.update_interval)
    {
        auto time = HAL::GetLocalTime();
        const char* weekday_list[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
        _data.date = fmt::format(
            "{}/{} {} {}", time->tm_mon + 1, time->tm_mday, weekday_list[time->tm_wday], time->tm_hour > 12 ? "PM" : "AM");

        _data.update_time_count = HAL::Millis();
    }

    // _data.date = "3/7 SAT";
    // _data.date = "12/23 SAT PM";
}

void WidgetCalendar::onRender()
{
    auto frame = _data.shape_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    HAL::GetCanvas()->setTextColor(TFT_WHITE);
    HAL::GetCanvas()->setTextDatum(middle_center);

    HAL::GetCanvas()->setTextSize(1);
    HAL::GetCanvas()->drawString(_data.date.c_str(), frame.x + frame.w / 2 + 1, frame.y + frame.h / 2 + 1);
}
