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
#include "../utils/system/system.h"

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppConsoleDaemon_Packer::getAppName() { return "ConsoleDaemon"; }

// Like setup()...
void AppConsoleDaemon::onResume() { spdlog::info("{} onResume", getAppName()); }

// Like loop()...
void AppConsoleDaemon::onRunning() { _update_buttons(); }

void AppConsoleDaemon::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }

void AppConsoleDaemon::_update_buttons()
{
    if (HAL::Millis() - _data.update_btn_time_count > _data.update_btn_interval)
    {
        Button::Update();

        if (Button::A()->wasClicked())
            HAL::Console().log("A o.O?");
        else if (Button::B()->wasClicked())
            HAL::Console().log("B o.O?");
        else if (Button::C()->wasClicked())
            HAL::Console().log("C o.O?");
        else if (Button::D()->wasClicked())
            HAL::Console().log("D o.O?");

        _data.update_btn_time_count = HAL::Millis();
    }
}
