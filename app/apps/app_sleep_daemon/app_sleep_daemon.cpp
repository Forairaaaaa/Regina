/**
 * @file app_sleep_daemon.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_sleep_daemon.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../utils/system/system.h"
#include "spdlog/spdlog.h"

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppSleepDaemon_Packer::getAppName() { return "SleepDaemon"; }

// Like setup()...
void AppSleepDaemon::onResume() { spdlog::info("{} onResume", getAppName()); }

// Like loop()...
void AppSleepDaemon::onRunning()
{
    // Check ready sleeping
    if (HAL::GetPowerState() == POWER::state_ready_to_sleep)
    {
        spdlog::info("ready, go to sleep");
        HAL::GoToSleep();
    }

    // Check power button
    if (HAL::Millis() - _data.check_pwr_btn_time_count > _data.check_pwr_btn_interval)
    {
        Button::Power()->update();
        if (Button::Power()->wasClicked())
        {
            // spdlog::info("pwr button clicked");
            if (HAL::GetPowerState() == POWER::state_awake)
            {
                // Fire event
                HAL::SetPowerState(POWER::state_going_sleep);
                spdlog::info("going to sleep");
            }
            else if (HAL::GetPowerState() == POWER::state_sleeping)
            {
                spdlog::info("wake up");
                HAL::WakeTheFuckUp();
            }
        }
        _data.check_pwr_btn_time_count = HAL::Millis();
    }
}

void AppSleepDaemon::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }
