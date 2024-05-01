/**
 * @file battery.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>
#include <smooth_ui_toolkit.h>

class WidgetBattery : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
        uint8_t battery_level = 100;
    };
    Data_t _data;
    void _reset_anim();

public:
    void onInit() override;
    void onUpdate(const SmoothUIToolKit::TimeSize_t& currentTime) override;
    void onRender() override;
};
