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
#include "widgets.h"
#include "../../../../assets/assets.h"
#include <mooncake.h>
#include <smooth_ui_toolkit.h>

using namespace SmoothUIToolKit;

static constexpr int _panel_startup_x = (128 - 24) / 2;
static constexpr int _panel_startup_y = 64 + 12;
static constexpr int _panel_startup_w = 24;
static constexpr int _panel_startup_h = 12;
static constexpr int _panel_x = 119;
static constexpr int _panel_y = 17;
static constexpr int _panel_w = 7;
static constexpr int _panel_h = 29;
static constexpr int _panel_r = 2;
static constexpr int _bar_mx = 2;
static constexpr int _bar_my = 2;

void WidgetBattery::onPopOut()
{
    constexpr int delay = 200;

    getTransition().jumpTo(_panel_startup_x, _panel_startup_y, _panel_startup_w, _panel_startup_h);
    getTransition().moveTo(_panel_x, _panel_y, _panel_w, _panel_h);

    getTransition().setEachDelay(delay, delay, delay + 70, delay + 70);
    getTransition().setEachDuration(500, 300, 500, 500);
}

void WidgetBattery::onHide()
{
    constexpr int delay = 60;

    getTransition().jumpTo(_panel_x, _panel_y, _panel_w, _panel_h);
    getTransition().moveTo(_panel_startup_x, _panel_startup_y, _panel_startup_w, _panel_startup_h);

    getTransition().setEachDelay(delay, delay + 70, delay + 70, delay + 70);
    getTransition().setEachDuration(500, 400, 500, 500);
}

void WidgetBattery::onUpdate() { _data.battery_level = HAL::GetBatteryPercentage(); }

void WidgetBattery::onRender()
{
    auto frame = getTransition().getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    int bar_width = frame.w - _bar_mx * 2;
    int bar_height = frame.h - _bar_my * 2;
    int consumed_height = bar_height - _data.battery_level * bar_height / 100;
    if (consumed_height < 0)
        consumed_height = 0;

    HAL::GetCanvas()->fillRect(frame.x + _bar_mx, frame.y + _bar_my, bar_width, bar_height, TFT_WHITE);
    HAL::GetCanvas()->fillRect(frame.x + _bar_mx, frame.y + _bar_my, bar_width, consumed_height, TFT_BLACK);
}
