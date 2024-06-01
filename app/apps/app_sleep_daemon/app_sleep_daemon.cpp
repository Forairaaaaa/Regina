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
#include "../../shared/shared.h"
#include "../utils/system/system.h"
#include "spdlog/spdlog.h"

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppSleepDaemon_Packer::getAppName() { return "SleepDaemon"; }

// Like setup()...
void AppSleepDaemon::onResume()
{
    spdlog::info("{} onResume", getAppName());
    SharedData::CupOfCoffee(HAL::Millis());
}

// Like loop()...
void AppSleepDaemon::onRunning()
{
    SharedData::BorrowData();

    // Check ready sleeping
    if (SharedData::GetPowerState() == POWER::state_ready_to_sleep)
    {
        spdlog::info("ready to sleep");
        SharedData::SetPowerState(POWER::state_sleeping);
        HAL::GoToSleep();
    }

    // Check power button
    if (HAL::Millis() - _data.check_pwr_btn_time_count > _data.check_pwr_btn_interval)
    {
        Button::Power()->update();
        if (Button::Power()->wasClicked())
        {
            // Kill ringtone
            if (HAL::IsRtttlPlaying())
            {
                HAL::StopPlayingRingtone();
            }

            // spdlog::info("pwr button clicked");
            else if (SharedData::GetPowerState() == POWER::state_awake)
            {
                // Fire event
                SharedData::SetPowerState(POWER::state_going_sleep);
                spdlog::info("going to sleep");
            }
            else if (SharedData::GetPowerState() == POWER::state_sleeping)
            {
                spdlog::info("wake up");
                SharedData::SetPowerState(POWER::state_awake);
                HAL::WakeTheFuckUp();
                SharedData::CupOfCoffee(HAL::Millis());
            }
        }
        _data.check_pwr_btn_time_count = HAL::Millis();
    }

    // Check auto sleep
    if (SharedData::GetPowerState() == POWER::state_awake)
    {
        // spdlog::info("{} {}", HAL::Millis(), SharedData::GetAwakeTime());
        if (HAL::Millis() - SharedData::GetAwakeTime() > HAL::GetSystemConfig().autoSleepTimeout)
        {
            spdlog::info("auto sleep");
            // Fire event
            SharedData::SetPowerState(POWER::state_going_sleep);
            spdlog::info("going to sleep");
        }
    }

    // Check new msg
    if (SharedData::GetPowerState() == POWER::state_sleeping)
    {
        if (!SharedData::Console().isEmpty())
        {
            spdlog::info("new msg, wake up");
            SharedData::SetPowerState(POWER::state_awake);
            HAL::WakeTheFuckUp();
            SharedData::CupOfCoffee(HAL::Millis());
        }
    }

    // Check audio fft come in
    if (!SharedData::GetEnableAudioFFTRendering() && SharedData::GetAudioFFTBuffer().size() != 0 &&
        SharedData::GetPowerState() == POWER::state_sleeping)
    {
        spdlog::info("get audio fft, wake up");
        SharedData::SetPowerState(POWER::state_awake);
        HAL::WakeTheFuckUp();
        SharedData::CupOfCoffee(HAL::Millis());
    }
    // Check audio fft update timeout
    else if (SharedData::GetEnableAudioFFTRendering() && SharedData::GetPowerState() == POWER::state_awake)
    {
        // If timeout, fuck back to terminal
        if (HAL::Millis() - SharedData::GetAudioFFTRenderTimecount() > 1000)
        {
            spdlog::info("audio fft update timeout");
            SharedData::GetEnableAudioFFTRendering() = false;
            SharedData::GetAudioFFTBuffer().clear();
        }
    }

    SharedData::ReturnData();
}

void AppSleepDaemon::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }
