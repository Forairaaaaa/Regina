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

class WidgetDesktop : public SmoothUIToolKit::Widgets::SmoothWidgetBase
{
private:
    struct Data_t
    {
        bool is_just_created = true;
    };
    Data_t _data;

public:
    void onInit() override;
    void onPopOut() override;
    void onHide() override;
    void onRender() override;
    void onPostRender() override;
};
