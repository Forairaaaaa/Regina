/**
 * @file components.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../../../hal/hal.h"
#include <smooth_ui_toolkit.h>
#include <cstdint>
#include <string>

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
    void onUpdate(const SmoothUIToolKit::TimeSize_t& currentTime) override;
    void onRender() override;
};

class WidgetCalendar : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
        std::string weekday;
        std::string date;
    };
    Data_t _data;
    void _reset_anim();

public:
    void onInit() override;
    void onUpdate(const SmoothUIToolKit::TimeSize_t& currentTime) override;
    void onRender() override;
};
