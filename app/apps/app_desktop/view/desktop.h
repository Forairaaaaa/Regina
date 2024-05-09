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
        bool is_just_created = true;
    };
    Data_t _data;

public:
    inline bool isAnimFinish() override { return _data.shape_trans.isFinish(); }
    void onInit() override;
    void onPopOut() override;
    void onRetract() override;
    void onUpdate() override;
    void onRender() override;
    void onPostRender() override;
};
