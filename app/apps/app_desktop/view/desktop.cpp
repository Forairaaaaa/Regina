/**
 * @file desktop.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "desktop.h"
#include <cstdint>
#include <smooth_ui_toolkit.h>
#include "../../../assets/assets.h"
#include "lgfx/v1/misc/enum.hpp"
#include "widgets/widgets.h"

using namespace SmoothUIToolKit;

static constexpr int _panel_startup_x = (128 - 24) / 2;
static constexpr int _panel_startup_y = 64 + 12;
static constexpr int _panel_startup_w = 24;
static constexpr int _panel_startup_h = 12;
static constexpr int _panel_x = 0;
static constexpr int _panel_y = 0;
static constexpr int _panel_w = 128;
static constexpr int _panel_h = 64;
static constexpr int _panel_r = 4;

void WidgetDesktop::onInit()
{
    // Child widgets
    addChild(new WidgetConsole);
    addChild(new WidgetBleStatus);
    addChild(new WidgetBattery);
    addChild(new WidgetClock);
    addChild(new WidgetCalendar);
}

void WidgetDesktop::onPopOut()
{
    getTransition().jumpTo(_panel_startup_x, _panel_startup_y, _panel_startup_w, _panel_startup_h);
    getTransition().moveTo(_panel_x, _panel_y, _panel_w, _panel_h);

    getTransition().setEachDuration(500, 400, 500, 500);
    getTransition().setEachDelay(70, 0, 70, 70);
}

void WidgetDesktop::onHide()
{
    constexpr int delay = 200;

    getTransition().jumpTo(_panel_x, _panel_y, _panel_w, _panel_h);
    getTransition().moveTo(_panel_startup_x, _panel_startup_y, _panel_startup_w, _panel_startup_h);

    getTransition().setEachDuration(400, 500, 400, 400);
    getTransition().setEachDelay(delay, delay + 70, delay, delay);

    // getTransition().setEachDuration(700, 500, 700, 500);
    // getTransition().setEachDelay(delay, delay, delay, delay);
}

void WidgetDesktop::onRender()
{
    if (isPoppedOut())
    {
        HAL::GetCanvas()->fillScreen(TFT_BLACK);
        HAL::GetCanvas()->fillRoundRect(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height(), _panel_r, TFT_WHITE);
    }
    else
    {
        auto frame = getTransition().getValue();
        HAL::GetCanvas()->fillScreen(TFT_BLACK);

        if (_data.is_just_created)
        {
            HAL::GetCanvas()->pushImage(0,
                                        frame.y - 103 - 12,
                                        AssetPool::GetImage().StartupAnim.warma_halftone_width,
                                        AssetPool::GetImage().StartupAnim.warma_halftone_height,
                                        AssetPool::GetImage().StartupAnim.warma_halftone);
        }

        HAL::GetCanvas()->fillRect(frame.x, frame.y, frame.w, frame.h, TFT_BLACK);
        HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_WHITE);
    }

    if (_data.is_just_created && isPoppedOut())
        _data.is_just_created = false;
}

void WidgetDesktop::onPostRender() { HAL::CanvasUpdate(); }
