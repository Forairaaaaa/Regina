/**
 * @file console.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "widgets.h"
#include "../../../../assets/assets.h"
#include <mooncake.h>
#include <smooth_ui_toolkit.h>

using namespace SmoothUIToolKit;

static constexpr int _panel_x = 2;
static constexpr int _panel_y = 2;
static constexpr int _panel_w = 115;
static constexpr int _panel_h = 45;
static constexpr int _panel_r = 4;
static constexpr int _canvas_w = 109;
static constexpr int _canvas_h = 39;
static constexpr int _canvas_mt = 3;
static constexpr int _canvas_ml = 3;

WidgetConsole::~WidgetConsole()
{
    if (HAL::GetConsoleCanvas() != nullptr)
    {
        delete HAL::GetConsoleCanvas();
        HAL::SetConsoleCanvas(nullptr);
    }
}

void WidgetConsole::onInit()
{
    if (HAL::GetConsoleCanvas() != nullptr)
        spdlog::error("canvas exist");
    else
    {
        auto terminal_canvas = new LGFX_SpriteFx(HAL::GetCanvas());
        terminal_canvas->createSprite(_canvas_w, _canvas_h);
        // terminal_canvas->fillScreen(TFT_WHITE);

        AssetPool::LoadFont12(terminal_canvas);
        terminal_canvas->setTextScroll(true);

        HAL::SetConsoleCanvas(terminal_canvas);

        HAL::Console().log("终端创建成功 :)");
        HAL::Console().setAutoNewLine(true);

        HAL::Console().log("机会, 烧冻鸡翅!");
        HAL::Console().log("我将, 点燃大海 >-<");
    }
}

void WidgetConsole::onPopOut()
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

    _data.msg_update_time_count = 0;
    _data.cursor_type = true;
}

void WidgetConsole::onUpdate()
{
    _data.shape_trans.update(HAL::Millis());
    if (!_data.shape_trans.isFinish())
        return;

    // Message
    if (HAL::Millis() - _data.msg_update_time_count > _data.msg_update_interval)
    {
        if (!HAL::Console().isEmpty())
        {
            // Remove old cursor
            HAL::GetConsoleCanvas()->fillRect(
                HAL::GetConsoleCanvas()->getCursorX(), HAL::GetConsoleCanvas()->getCursorY() + 10, 6, 3, TFT_BLACK);

            char shit = 0;
            HAL::Console().get(shit);
            HAL::GetConsoleCanvas()->print(shit);

            // New cursor
            HAL::GetConsoleCanvas()->fillRect(
                HAL::GetConsoleCanvas()->getCursorX(), HAL::GetConsoleCanvas()->getCursorY() + 10, 6, 3, TFT_WHITE);
        }

        _data.msg_update_time_count = HAL::Millis();
    }

    // Cursor blink
    if (HAL::Millis() - _data.cursor_update_time_count > _data.cursor_update_interval)
    {
        _data.cursor_type = !_data.cursor_type;

        HAL::GetConsoleCanvas()->fillRect(HAL::GetConsoleCanvas()->getCursorX(),
                                          HAL::GetConsoleCanvas()->getCursorY() + 10,
                                          6,
                                          3,
                                          _data.cursor_type ? TFT_WHITE : TFT_BLACK);
        // spdlog::info(
        //     "{} {} {}", HAL::GetConsoleCanvas()->getCursorX(), HAL::GetConsoleCanvas()->getCursorY(), _data.cursor_type);

        _data.cursor_update_time_count = HAL::Millis();
    }
}

void WidgetConsole::onRender()
{
    // panel
    auto frame = _data.shape_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    // Console
    if (_data.shape_trans.isFinish())
    {
        HAL::GetConsoleCanvas()->pushSprite(_panel_x + _canvas_ml, _panel_y + _canvas_mt);
    }
}
