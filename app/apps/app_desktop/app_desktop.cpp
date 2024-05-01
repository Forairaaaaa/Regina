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
#include "lgfx/v1/misc/enum.hpp"

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppDesktop_Packer::getAppName() { return "Desktop"; }

// Icon
void* AppDesktop_Packer::getAppIcon() { return nullptr; }

void AppDesktop::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    setAllowBgRunning(true);
    startApp();

    // Init components
    _data.terminal.init();
}

// Like setup()...
void AppDesktop::onResume() { spdlog::info("{} onResume", getAppName()); }

// Like loop()...
void AppDesktop::onRunning()
{
    /* --------------------------------- Update --------------------------------- */
    _data.terminal.update();

    /* --------------------------------- Render --------------------------------- */
    HAL::GetCanvas()->fillRoundRect(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height(), 8, TFT_WHITE);
    _data.terminal.render();
    HAL::CanvasUpdate();
}

void AppDesktop::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }
