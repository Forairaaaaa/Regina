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
#include "terminal.h"
#include <mooncake.h>
#include "core/easing_path/easing_path.h"
#include "hal/utils/lgfx_fx/lgfx_fx.h"
#include "lgfx/v1/misc/enum.hpp"
#include "spdlog/spdlog.h"

using namespace SmoothUIToolKit;

static constexpr int _panel_x = 2;
static constexpr int _panel_y = 2;
static constexpr int _panel_w = 115;
static constexpr int _panel_h = 31;
static constexpr int _panel_r = 8;
static constexpr int _canvas_w = 103;
static constexpr int _canvas_h = 29;
static constexpr int _canvas_mt = 1;
static constexpr int _canvas_ml = 6;

void Terminal::_reset_anim()
{
    _data.position_trans.setTransitionPath(EasingPath::easeOutBack);
    _data.position_trans.jumpTo(_panel_x, 70, 24, 24);
    _data.position_trans.moveTo(_panel_x, _panel_y, _panel_w, _panel_h);
    _data.position_trans.setDuration(400);

    _data.position_trans.getXTransition().setDelay(200);
}

Terminal::~Terminal()
{
    if (_data.terminal_canvas != nullptr)
        delete _data.terminal_canvas;
}

void Terminal::init()
{
    if (_data.terminal_canvas != nullptr)
        spdlog::error("canvas exist");
    else
    {
        _data.terminal_canvas = new LGFX_SpriteFx(HAL::GetCanvas());
        _data.terminal_canvas->createSprite(_canvas_w, _canvas_h);
        // _data.terminal_canvas->fillScreen(TFT_WHITE);
    }

    _reset_anim();
}

void Terminal::update() { _data.position_trans.update(HAL::Millis()); }

void Terminal::render()
{
    /* ---------------------------------- Panel --------------------------------- */
    auto frame = _data.position_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    /* -------------------------------- Terminal -------------------------------- */
    if (_data.position_trans.isFinish())
    {
        _data.terminal_canvas->pushSprite(_panel_x + _canvas_ml, _panel_y + _canvas_mt);
    }
}
