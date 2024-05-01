/**
 * @file battery.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "battery.h"
#include <mooncake.h>
#include <smooth_ui_toolkit.h>
#include "../../../assets/assets.h"
#include "lgfx/v1/misc/enum.hpp"
#include "spdlog/spdlog.h"

using namespace SmoothUIToolKit;

static constexpr int _panel_x = 119;
static constexpr int _panel_y = 5;
static constexpr int _panel_w = 7;
static constexpr int _panel_h = 25;
static constexpr int _panel_r = 2;
static constexpr int _bar_mx = 2;
static constexpr int _bar_my = 2;

void WidgetBattery::onInit() { _reset_anim(); }

void WidgetBattery::onUpdate(const TimeSize_t& currentTime)
{
    _data.shape_trans.update(HAL::Millis());
    _data.battery_level = HAL::GetBatteryPercentage();
}

void WidgetBattery::onRender()
{
    auto frame = _data.shape_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    int bar_width = frame.w - _bar_mx * 2;
    int bar_height = frame.h - _bar_my * 2;
    int consumed_height = bar_height - _data.battery_level * bar_height / 100;
    if (consumed_height < 0)
        consumed_height = 0;

    HAL::GetCanvas()->fillRect(frame.x + _bar_mx, frame.y + _bar_my, bar_width, bar_height, TFT_WHITE);
    HAL::GetCanvas()->fillRect(frame.x + _bar_mx, frame.y + _bar_my, bar_width, consumed_height, TFT_BLACK);
}

void WidgetBattery::_reset_anim()
{
    constexpr int delay = 200;

    _data.shape_trans.jumpTo((HAL::GetCanvas()->width() + 24) / 2, HAL::GetCanvas()->height(), 24, 12);
    _data.shape_trans.moveTo(_panel_x, _panel_y, _panel_w, _panel_h);

    _data.shape_trans.setDelay(delay);
    _data.shape_trans.setDuration(700);
    // _data.position_trans.setTransitionPath(EasingPath::easeOutBack);

    _data.shape_trans.getYTransition().setDuration(500);
    // _data.shape_trans.getXTransition().setDelay(delay + 70);
    _data.shape_trans.getWTransition().setDelay(delay + 70);
    _data.shape_trans.getHTransition().setDelay(delay + 70);
}
