/**
 * @file app_input_daemon.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_input_daemon.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../../shared/shared.h"
#include "../../shared/shared.h"
#include "../utils/system/system.h"
#include <cstdint>

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppInputDaemon_Packer::getAppName() { return "ConsoleDaemon"; }

void AppInputDaemon::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    setAllowBgRunning(true);
    startApp();
}

void AppInputDaemon::onResume()
{
    spdlog::info("{} onResume", getAppName());

    _data.last_dial_a_value = HAL::GetDialValue(DIAL::DIAL_A);
    _data.last_dial_b_value = HAL::GetDialValue(DIAL::DIAL_B);
    _data.last_dial_a_count = HAL::GetDialCount(DIAL::DIAL_A);
    _data.last_dial_b_count = HAL::GetDialCount(DIAL::DIAL_B);
}

void AppInputDaemon::onRunning()
{
    // Check is sleeping
    if (SharedData::GetPowerState() == POWER::state_sleeping)
    {
        closeApp();
        return;
    }

    _update_buttons();
}

void AppInputDaemon::onRunningBG()
{
    // Check is sleeping
    if (SharedData::GetPowerState() == POWER::state_awake)
    {
        startApp();
    }
}

void AppInputDaemon::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }

void AppInputDaemon::_update_buttons()
{
    if (HAL::Millis() - _data.update_btn_time_count > _data.update_btn_interval)
    {
        Button::Update();

        auto pipe_value_num = SharedData::Console().valueNum();

        if (Button::A()->wasClicked())
        {
            SharedData::Console().log(">A<");
            HAL::BleKeyBoardWrite(BLE_KB::KEY_MEDIA_PREVIOUS_TRACK);
        }
        else if (Button::B()->wasClicked())
        {
            SharedData::Console().log(">B<");
            HAL::BleKeyBoardWrite(BLE_KB::KEY_MEDIA_PLAY_PAUSE);
        }
        else if (Button::C()->wasClicked())
        {
            SharedData::Console().log(">C<");
            HAL::BleKeyBoardWrite(BLE_KB::KEY_MEDIA_NEXT_TRACK);
        }
        else if (Button::D()->wasClicked())
        {
            SharedData::Console().log(">D<");
            HAL::BleKeyBoardWrite(BLE_KB::KEY_MEDIA_MUTE);
        }

        if (SharedData::Console().valueNum() != pipe_value_num)
            SharedData::CupOfCoffee(HAL::Millis());

        // 来都来了
        _update_dials();

        _data.update_btn_time_count = HAL::Millis();
    }
}

void AppInputDaemon::_update_dials()
{
    auto pipe_value_num = SharedData::Console().valueNum();
    uint8_t new_value = 0;

    new_value = HAL::GetDialValue(DIAL::DIAL_A);
    if (new_value != _data.last_dial_a_value)
    {
        _data.last_dial_a_value = new_value;
        SharedData::Console().log("OA>{:X}", new_value);

        if (HAL::GetDialCount(DIAL::DIAL_A) > _data.last_dial_a_count)
            HAL::BleKeyBoardWrite(BLE_KB::KEY_UP_ARROW);
        else
            HAL::BleKeyBoardWrite(BLE_KB::KEY_DOWN_ARROW);
    }

    new_value = HAL::GetDialValue(DIAL::DIAL_B);
    if (new_value != _data.last_dial_b_value)
    {
        _data.last_dial_b_value = new_value;
        SharedData::Console().log("OB>{:X}", new_value);

        if (HAL::GetDialCount(DIAL::DIAL_B) > _data.last_dial_b_count)
            HAL::BleKeyBoardWrite(BLE_KB::KEY_MEDIA_VOLUME_UP);
        else
            HAL::BleKeyBoardWrite(BLE_KB::KEY_MEDIA_VOLUME_DOWN);
    }

    if (SharedData::Console().valueNum() != pipe_value_num)
        SharedData::CupOfCoffee(HAL::Millis());
}
