/**
 * @file terminal.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "components.h"
#include "../../../../assets/assets.h"
#include <mooncake.h>
#include <smooth_ui_toolkit.h>

using namespace SmoothUIToolKit;

static constexpr int _panel_x = 2;
static constexpr int _panel_y = 2;
static constexpr int _panel_w = 115;
static constexpr int _panel_h = 31;
static constexpr int _panel_r = 8;
static constexpr int _canvas_w = 105;
static constexpr int _canvas_h = 27;
static constexpr int _canvas_mt = 2;
static constexpr int _canvas_ml = 5;

void WidgetTerminal::_reset_anim()
{
    constexpr int delay = 260;

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

WidgetTerminal::~WidgetTerminal()
{
    if (_data.terminal_canvas != nullptr)
        delete _data.terminal_canvas;
}

void WidgetTerminal::onInit()
{
    if (_data.terminal_canvas != nullptr)
        spdlog::error("canvas exist");
    else
    {
        _data.terminal_canvas = new LGFX_SpriteFx(HAL::GetCanvas());
        _data.terminal_canvas->createSprite(_canvas_w, _canvas_h);
        // _data.terminal_canvas->fillScreen(TFT_WHITE);

        AssetPool::LoadFont12(_data.terminal_canvas);
        _data.terminal_canvas->setTextScroll(true);
    }

    _reset_anim();
}

void WidgetTerminal::onReset() { _reset_anim(); }

void WidgetTerminal::onUpdate(const SmoothUIToolKit::TimeSize_t& currentTime)
{
    _data.shape_trans.update(currentTime);

    if (_data.shape_trans.isFinish())
    {
        static int shit = 0;
        shit++;
        _data.terminal_canvas->printf("%d", shit);

        // HAL::Delay(100);
    }
}

void WidgetTerminal::onRender()
{
    /* ---------------------------------- Panel --------------------------------- */
    auto frame = _data.shape_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    /* -------------------------------- Terminal -------------------------------- */
    if (_data.shape_trans.isFinish())
    {
        _data.terminal_canvas->pushSprite(_panel_x + _canvas_ml, _panel_y + _canvas_mt);
    }
}
