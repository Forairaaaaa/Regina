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
#include <smooth_ui_toolkit.h>
#include "../../../assets/assets.h"
#include "widgets/widgets.h"

using namespace SmoothUIToolKit;

static constexpr int _panel_startup_x = (128 - 24) / 2;
static constexpr int _panel_startup_y = 64;
static constexpr int _panel_startup_w = 24;
static constexpr int _panel_startup_h = 12;
static constexpr int _panel_r = 4;

void WidgetDesktop::onInit()
{
    // // Child widgets
    // addChild(new WidgetConsole);
    // addChild(new WidgetBleStatus);
    // addChild(new WidgetBattery);
    // addChild(new WidgetClock);
    // addChild(new WidgetCalendar);
}

void WidgetDesktop::onPopOut()
{
    _data.shape_trans.jumpTo(_panel_startup_x, _panel_startup_y, _panel_startup_w, _panel_startup_h);
    _data.shape_trans.moveTo(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height());

    _data.shape_trans.setDuration(400);
    // _data.shape_trans.setTransitionPath(EasingPath::easeOutBack);

    _data.shape_trans.getYTransition().setDuration(500);
    _data.shape_trans.getXTransition().setDelay(70);
    _data.shape_trans.getWTransition().setDelay(70);
    _data.shape_trans.getHTransition().setDelay(70);
}

void WidgetDesktop::onRetract()
{
    _data.shape_trans.jumpTo(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height());
    _data.shape_trans.moveTo(_panel_startup_x, _panel_startup_y, _panel_startup_w, _panel_startup_h);

    _data.shape_trans.setDuration(400);
    // _data.shape_trans.setTransitionPath(EasingPath::easeOutBack);

    _data.shape_trans.getYTransition().setDuration(500);
    _data.shape_trans.getXTransition().setDelay(70);
    _data.shape_trans.getWTransition().setDelay(70);
    _data.shape_trans.getHTransition().setDelay(70);
}

void WidgetDesktop::onUpdate() { _data.shape_trans.update(HAL::Millis()); }

void WidgetDesktop::onRender()
{
    if (isPoppedOut())
    {
        HAL::GetCanvas()->fillScreen(TFT_BLACK);
        HAL::GetCanvas()->fillRoundRect(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height(), _panel_r, TFT_WHITE);
    }
    else
    {
        auto frame = _data.shape_trans.getValue();
        HAL::GetCanvas()->fillScreen(TFT_BLACK);

        if (_data.is_just_created)
        {
            HAL::GetCanvas()->pushImage(0,
                                        frame.y - 103,
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
