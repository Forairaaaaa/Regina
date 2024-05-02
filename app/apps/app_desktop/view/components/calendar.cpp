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
#include "components.h"
#include "../../../../assets/assets.h"
#include "hal/hal.h"
#include <mooncake.h>
#include <smooth_ui_toolkit.h>

using namespace SmoothUIToolKit;

static constexpr int _panel_x = 79;
static constexpr int _panel_y = 35;
static constexpr int _panel_w = 47;
static constexpr int _panel_h = 27;
static constexpr int _panel_r = 4;

void WidgetCalendar::_reset_anim()
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
}

void WidgetCalendar::onInit() { _reset_anim(); }

void WidgetCalendar::onUpdate(const TimeSize_t& currentTime)
{
    _data.shape_trans.update(HAL::Millis());

    auto time = HAL::GetLocalTime();

    const char* weekday_list[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    _data.weekday = weekday_list[time->tm_wday];

    _data.date = spdlog::fmt_lib::format("{}/{}", time->tm_mon + 1, time->tm_mday);

    // _data.weekday = "SAT";
    // _data.date = "3/7";
}

void WidgetCalendar::onRender()
{
    auto frame = _data.shape_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);
    HAL::GetCanvas()->drawFastHLine(frame.x, frame.y + frame.h / 2, frame.w, TFT_WHITE);

    HAL::GetCanvas()->setTextColor(TFT_WHITE);
    HAL::GetCanvas()->setTextDatum(middle_center);

    HAL::GetCanvas()->setTextSize(1);

    int x = frame.x + frame.w / 2 + 1;
    HAL::GetCanvas()->drawString(_data.weekday.c_str(), x, frame.y + frame.h / 4 + 1);
    HAL::GetCanvas()->drawString(_data.date.c_str(), x, frame.y + frame.h / 4 * 3 + 3);
}
