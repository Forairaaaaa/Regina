/**
 * @file widgets.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "core/types/types.h"
#include <smooth_ui_toolkit.h>
#include <cstdint>
#include <string>

class WidgetTerminal : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
    };
    Data_t _data;
    void _reset_anim();

public:
    ~WidgetTerminal();

    void onInit() override;
    void onReset() override;
    void onUpdate() override;
    void onRender() override;
};

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
    void onUpdate() override;
    void onRender() override;
};

class WidgetClock : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
        std::string time;
    };
    Data_t _data;
    void _reset_anim();

public:
    void onInit() override;
    void onUpdate() override;
    void onRender() override;
};

class WidgetCalendar : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
        std::string date;
    };
    Data_t _data;
    void _reset_anim();

public:
    void onInit() override;
    void onUpdate() override;
    void onRender() override;
};

class WidgetBleStatus : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
        uint32_t anim_time_count = 0;
        SmoothUIToolKit::Vector2D_t anim_cursor;
        bool anim_mask_type = false;
    };
    Data_t _data;
    void _reset_anim();
    bool _get_next_anim_cursor(int& x, int& y);

public:
    void onInit() override;
    void onUpdate() override;
    void onRender() override;
};