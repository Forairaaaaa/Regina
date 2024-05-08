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

void WidgetDesktop::_reset_anim()
{
    _data.shape_trans.jumpTo((HAL::GetCanvas()->width() - 24) / 2, HAL::GetCanvas()->height(), 24, 12);
    _data.shape_trans.moveTo(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height());

    _data.shape_trans.setDuration(400);
    // _data.shape_trans.setTransitionPath(EasingPath::easeOutBack);

    _data.shape_trans.getYTransition().setDuration(500);
    _data.shape_trans.getXTransition().setDelay(70);
    _data.shape_trans.getWTransition().setDelay(70);
    _data.shape_trans.getHTransition().setDelay(70);
}

void WidgetDesktop::onInit()
{
    _reset_anim();

    // Child widgets
    addChild(new WidgetConsole);
    addChild(new WidgetBleStatus);
    addChild(new WidgetBattery);
    addChild(new WidgetClock);
    addChild(new WidgetCalendar);
}

void WidgetDesktop::onReset() { _reset_anim(); }

void WidgetDesktop::onUpdate() { _data.shape_trans.update(HAL::Millis()); }

void WidgetDesktop::onRender()
{
    if (_data.shape_trans.isFinish())
        HAL::GetCanvas()->fillRoundRect(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height(), 8, TFT_WHITE);
    else
    {
        auto frame = _data.shape_trans.getValue();
        HAL::GetCanvas()->fillScreen(TFT_BLACK);

        HAL::GetCanvas()->pushImage(0,
                                    frame.y - 103,
                                    AssetPool::GetImage().StartupAnim.warma_halftone_width,
                                    AssetPool::GetImage().StartupAnim.warma_halftone_height,
                                    AssetPool::GetImage().StartupAnim.warma_halftone);
        HAL::GetCanvas()->fillRect(frame.x, frame.y, frame.w, frame.h, TFT_BLACK);
        HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, 4, TFT_WHITE);
    }
}

void WidgetDesktop::onPostRender() { HAL::CanvasUpdate(); }
