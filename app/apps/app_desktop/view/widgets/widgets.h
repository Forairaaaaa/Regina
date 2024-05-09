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

class WidgetConsole : public SmoothUIToolKit::Widgets::WidgetBase
{
private:
    struct Data_t
    {
        SmoothUIToolKit::Transition4D shape_trans;
        uint32_t msg_update_time_count = 0;
        uint32_t msg_update_interval = 20;
        uint32_t cursor_update_time_count = 0;
        uint32_t cursor_update_interval = 500;
        bool cursor_type = true;
    };
    Data_t _data;

public:
    ~WidgetConsole();

    // inline bool isAnimFinish() override { return _data.shape_trans.isFinish(); }
    void onInit() override;
    void onPopOut() override;
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

public:
    // inline bool isAnimFinish() override { return _data.shape_trans.isFinish(); }
    void onPopOut() override;
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
        uint32_t update_time_count = 0;
        uint32_t update_interval = 1000;
        bool colon_type = true;
    };
    Data_t _data;

public:
    // inline bool isAnimFinish() override { return _data.shape_trans.isFinish(); }
    void onPopOut() override;
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
        uint32_t update_time_count = 0;
        uint32_t update_interval = 1000;
    };
    Data_t _data;

public:
    // inline bool isAnimFinish() override { return _data.shape_trans.isFinish(); }
    void onPopOut() override;
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
    bool _get_next_anim_cursor(int& x, int& y);

public:
    // inline bool isAnimFinish() override { return _data.shape_trans.isFinish(); }
    void onPopOut() override;
    void onUpdate() override;
    void onRender() override;
};
