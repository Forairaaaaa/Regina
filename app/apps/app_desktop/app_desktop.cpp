/**
 * @file app_desktop.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_desktop.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../../shared/shared.h"
#include "../utils/system/system.h"
#include "spdlog/spdlog.h"

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;
using namespace SmoothUIToolKit;

// App name
const char* AppDesktop_Packer::getAppName() { return "Desktop"; }

// Icon
void* AppDesktop_Packer::getAppIcon() { return nullptr; }

void AppDesktop::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    _data.widget_desktop.init();
    _data.widget_desktop.popOut();
}

// Like setup()...
void AppDesktop::onResume() { spdlog::info("{} onResume", getAppName()); }

// Like loop()...
void AppDesktop::onRunning()
{
    // Normal update
    if (SharedData::GetPowerState() != POWER::state_sleeping)
        _data.widget_desktop.update(HAL::Millis());

    // spdlog::info("{} {} {} {}",
    //              _data.widget_desktop.isPoppedOut(),
    //              _data.widget_desktop.isPoppingOut(),
    //              _data.widget_desktop.isHidden(),
    //              _data.widget_desktop.isHidding());

    // Pop out
    if (SharedData::GetPowerState() == POWER::state_awake && _data.widget_desktop.isHidden())
        _data.widget_desktop.popOut();

    // Hide
    else if (SharedData::GetPowerState() == POWER::state_going_sleep)
    {
        if (_data.widget_desktop.isPoppedOut())
            _data.widget_desktop.hide();

        // Ready to sleep
        if (_data.widget_desktop.isHidden())
            SharedData::SetPowerState(POWER::state_ready_to_sleep);
    }
}

void AppDesktop::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }
