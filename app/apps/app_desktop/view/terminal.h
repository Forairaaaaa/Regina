/**
 * @file terminal.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../../hal/hal.h"
#include <smooth_ui_toolkit.h>

class WidgetTerminal : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
        LGFX_SpriteFx* terminal_canvas = nullptr;
    };
    Data_t _data;
    void _reset_anim();

public:
    ~WidgetTerminal();

    void onInit() override;
    void onReset() override;
    void onUpdate(const SmoothUIToolKit::TimeSize_t& currentTime) override;
    void onRender() override;
};
