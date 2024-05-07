/**
 * @file ble_status.cpp
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
#include "lgfx/v1/misc/enum.hpp"
#include "spdlog/spdlog.h"
#include <mooncake.h>
#include <smooth_ui_toolkit.h>

using namespace SmoothUIToolKit;

static constexpr int _panel_x = 119;
static constexpr int _panel_y = 4;
static constexpr int _panel_w = 7;
static constexpr int _panel_h = 11;
static constexpr int _panel_r = 2;
static constexpr int _bar_mx = 2;
static constexpr int _bar_my = 2;

void WidgetBleStatus::_reset_anim()
{
    constexpr int delay = 100;

    _data.shape_trans.jumpTo((HAL::GetCanvas()->width() + 24) / 2, HAL::GetCanvas()->height(), 24, 12);
    _data.shape_trans.moveTo(_panel_x, _panel_y, _panel_w, _panel_h);

    _data.shape_trans.setDelay(delay);
    _data.shape_trans.setDuration(500);
    // _data.position_trans.setTransitionPath(EasingPath::easeOutBack);

    _data.shape_trans.getYTransition().setDuration(300);
    // _data.shape_trans.getXTransition().setDelay(delay + 70);
    _data.shape_trans.getWTransition().setDelay(delay + 70);
    _data.shape_trans.getHTransition().setDelay(delay + 70);

    _data.anim_time_count = 0;
    _data.anim_cursor.reset(_panel_x + _bar_mx, _panel_y + _bar_my);
}

void WidgetBleStatus::onInit() { _reset_anim(); }

void WidgetBleStatus::onUpdate() { _data.shape_trans.update(HAL::Millis()); }

void WidgetBleStatus::onRender()
{
    auto frame = _data.shape_trans.getValue();
    HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, _panel_r, TFT_BLACK);

    if (!_data.shape_trans.isFinish() || HAL::IsBleConnected())
    {
        HAL::GetCanvas()->fillRect(
            frame.x + _bar_mx, frame.y + _bar_my, frame.w - _bar_mx * 2, frame.h - _bar_my * 2, TFT_WHITE);
    }
    else
    {
        // Render mask
        HAL::GetCanvas()->fillRect(frame.x + _bar_mx,
                                   frame.y + _bar_my,
                                   frame.w - _bar_mx * 2,
                                   frame.h - _bar_my * 2,
                                   _data.anim_mask_type ? TFT_BLACK : TFT_WHITE);

        int x = _panel_x + _bar_mx;
        int y = _panel_y + _bar_my;
        while (1)
        {
            if (_data.anim_cursor.equals(x, y))
                break;

            HAL::GetCanvas()->drawPixel(x, y, _data.anim_mask_type ? TFT_WHITE : TFT_BLACK);

            _get_next_anim_cursor(x, y);
        }

        // Update mask
        if (HAL::Millis() - _data.anim_time_count > 100)
        {
            if (_get_next_anim_cursor(_data.anim_cursor.x, _data.anim_cursor.y))
                _data.anim_mask_type = !_data.anim_mask_type;

            // spdlog::info("{} {} {}", _data.anim_cursor.x, _data.anim_cursor.y, _data.anim_mask_type);

            _data.anim_time_count = HAL::Millis();
        }
    }
}

bool WidgetBleStatus::_get_next_anim_cursor(int& x, int& y)
{
    bool reset = false;

    x++;
    // New line
    if (x >= _panel_x + _panel_w - _bar_mx)
    {
        x = _panel_x + _bar_mx;
        y++;
        // Reset
        if (y >= _panel_y + _panel_h - _bar_my)
        {
            _data.anim_cursor.reset(_panel_x + _bar_mx, _panel_y + _bar_my);
            reset = true;
        }
    }

    return reset;
}
