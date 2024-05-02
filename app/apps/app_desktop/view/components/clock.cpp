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
#include "components.h"
#include "../../../../assets/assets.h"
#include "hal/hal.h"
#include "lgfx/v1/misc/enum.hpp"
#include "spdlog/spdlog.h"
#include <mooncake.h>
#include <smooth_ui_toolkit.h>

using namespace SmoothUIToolKit;

static constexpr int _panel_x = 2;
static constexpr int _panel_y = 35;
static constexpr int _panel_w = 75;
static constexpr int _panel_h = 27;
static constexpr int _panel_r = 8;

void WidgetClock::_reset_anim()
{
    constexpr int delay = 400;

    _data.shape_trans.jumpTo((HAL::GetCanvas()->width() - 24) / 2 - 24, HAL::GetCanvas()->height(), 24, 20);
    _data.shape_trans.moveTo(_panel_x, _panel_y, _panel_w, _panel_h);

    _data.shape_trans.setDelay(delay);
    _data.shape_trans.setDuration(500);
    // _data.shape_trans.setTransitionPath(EasingPath::easeOutBack);

    _data.shape_trans.getYTransition().setDuration(300);
    _data.shape_trans.getXTransition().setDelay(delay + 70);
    _data.shape_trans.getWTransition().setDelay(delay + 70);
    _data.shape_trans.getHTransition().setDelay(delay + 70);
}

void WidgetClock::onInit() { _reset_anim(); }

void WidgetClock::onUpdate(const TimeSize_t& currentTime)
{
    _data.shape_trans.update(HAL::Millis());

    auto time = HAL::GetLocalTime();
    _data.time = spdlog::fmt_lib::format("{:02d}:{:02d}", time->tm_hour, time->tm_min);
    // spdlog::info("{}", _data.time);

    // _data.time = "22:33";
}

void WidgetClock::onRender()
{
    auto frame = _data.shape_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    HAL::GetCanvas()->setTextColor(TFT_WHITE);
    HAL::GetCanvas()->setTextDatum(middle_center);

    // float font_size = ((float)frame.h - ((float)_panel_h - 24)) / 12;
    // spdlog::info("{}", font_size);
    // HAL::GetCanvas()->setTextSize(font_size);
    HAL::GetCanvas()->setTextSize(2);

    HAL::GetCanvas()->drawString(_data.time.c_str(), frame.x + frame.w / 2 + 1, frame.y + frame.h / 2 + 1);
}
