/**
 * @file desktop.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <smooth_ui_toolkit.h>

class WidgetDesktop : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
    };
    Data_t _data;

    void _reset_anim();

public:
    void onInit() override;
    void onReset() override;
    void onUpdate() override;
    void onRender() override;
    void onPostRender() override;
};
