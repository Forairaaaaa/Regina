/**
 * @file app_console_daemon.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_console_daemon.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../../shared/shared.h"
#include "../../shared/shared.h"
#include "../utils/system/system.h"
#include <cstdint>

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppConsoleDaemon_Packer::getAppName() { return "ConsoleDaemon"; }

void AppConsoleDaemon::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    setAllowBgRunning(true);
    startApp();
}

void AppConsoleDaemon::onResume()
{
    spdlog::info("{} onResume", getAppName());

    _data.last_dial_a_value = HAL::GetDialValue(DIAL::DIAL_A);
    _data.last_dial_b_value = HAL::GetDialValue(DIAL::DIAL_B);
}

void AppConsoleDaemon::onRunning()
{
    // Check is sleeping
    if (SharedData::GetPowerState() == POWER::state_sleeping)
    {
        closeApp();
        return;
    }

    _update_buttons();
}

void AppConsoleDaemon::onRunningBG()
{
    // Check is sleeping
    if (SharedData::GetPowerState() == POWER::state_awake)
    {
        startApp();
    }
}

void AppConsoleDaemon::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }

void AppConsoleDaemon::_update_buttons()
{
    if (HAL::Millis() - _data.update_btn_time_count > _data.update_btn_interval)
    {
        Button::Update();

        auto pipe_value_num = SharedData::Console().valueNum();

        if (Button::A()->wasClicked())
            SharedData::Console().log(">A<");
        else if (Button::B()->wasClicked())
            SharedData::Console().log(">B<");
        else if (Button::C()->wasClicked())
            SharedData::Console().log(">C<");
        else if (Button::D()->wasClicked())
            SharedData::Console().log(">D<");

        if (SharedData::Console().valueNum() != pipe_value_num)
            SharedData::CupOfCoffee(HAL::Millis());

        // 来都来了
        _update_dials();

        _data.update_btn_time_count = HAL::Millis();
    }
}

void AppConsoleDaemon::_update_dials()
{
    uint8_t new_value = 0;

    new_value = HAL::GetDialValue(DIAL::DIAL_A);
    if (new_value != _data.last_dial_a_value)
    {
        _data.last_dial_a_value = new_value;
        SharedData::Console().log("OA>{:X}", new_value);
        SharedData::CupOfCoffee(HAL::Millis());
    }

    new_value = HAL::GetDialValue(DIAL::DIAL_B);
    if (new_value != _data.last_dial_b_value)
    {
        _data.last_dial_b_value = new_value;
        SharedData::Console().log("OB>{:X}", new_value);
        SharedData::CupOfCoffee(HAL::Millis());
    }
}
