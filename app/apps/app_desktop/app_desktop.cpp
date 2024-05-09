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
#include "../utils/system/system.h"

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

    setAllowBgRunning(true);
    startApp();

    _data.widget_desktop.init();
}

// Like setup()...
void AppDesktop::onResume() { spdlog::info("{} onResume", getAppName()); }

// Like loop()...
void AppDesktop::onRunning() { _data.widget_desktop.update(); }

void AppDesktop::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }
