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

class Terminal
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D position_trans;

        LGFX_SpriteFx* terminal_canvas = nullptr;
    };
    Data_t _data;
    void _reset_anim();

public:
    ~Terminal();

    void init();
    void update();
    void render();
};
