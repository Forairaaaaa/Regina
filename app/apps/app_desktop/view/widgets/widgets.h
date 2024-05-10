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

class WidgetConsole : public SmoothUIToolKit::Widgets::SmoothWidgetBase
{
private:
    struct Data_t
    {
        uint32_t msg_update_time_count = 0;
        uint32_t msg_update_interval = 20;
        uint32_t cursor_update_time_count = 0;
        uint32_t cursor_update_interval = 500;
        bool cursor_type = true;
    };
    Data_t _data;

public:
    ~WidgetConsole();

    void onInit() override;
    void onPopOut() override;
    void onHide() override;
    void onUpdate() override;
    void onRender() override;
};

class WidgetBleStatus : public SmoothUIToolKit::Widgets::SmoothWidgetBase
{
private:
    struct Data_t
    {
        uint32_t anim_time_count = 0;
        SmoothUIToolKit::Vector2D_t anim_cursor;
        bool anim_mask_type = false;
    };
    Data_t _data;
    bool _get_next_anim_cursor(int& x, int& y);

public:
    void onPopOut() override;
    void onHide() override;
    void onRender() override;
};

class WidgetBattery : public SmoothUIToolKit::Widgets::SmoothWidgetBase
{
private:
    struct Data_t
    {
        uint8_t battery_level = 100;
    };
    Data_t _data;

public:
    void onPopOut() override;
    void onHide() override;
    void onUpdate() override;
    void onRender() override;
};

class WidgetClock : public SmoothUIToolKit::Widgets::SmoothWidgetBase
{
private:
    struct Data_t
    {
        std::string time;
        uint32_t update_time_count = 0;
        uint32_t update_interval = 1000;
        bool colon_type = true;
    };
    Data_t _data;

public:
    void onPopOut() override;
    void onHide() override;
    void onUpdate() override;
    void onRender() override;
};

class WidgetCalendar : public SmoothUIToolKit::Widgets::SmoothWidgetBase
{
private:
    struct Data_t
    {
        std::string date;
        uint32_t update_time_count = 0;
        uint32_t update_interval = 1000;
    };
    Data_t _data;

public:
    void onPopOut() override;
    void onHide() override;
    void onUpdate() override;
    void onRender() override;
};
