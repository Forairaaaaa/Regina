/**
 * @file app_launcher.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_launcher.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../utils/system/system.h"
#include "lgfx/v1/misc/enum.hpp"

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppLauncher_Packer::getAppName() { return "AppLauncher"; }

// Icon
void* AppLauncher_Packer::getAppIcon() { return nullptr; }

void AppLauncher::onCreate()
{
    setAllowBgRunning(true);
    startApp();
}

// Like setup()...
void AppLauncher::onResume()
{
    spdlog::info("{} onResume", getAppName());
    HAL::GetCanvas()->setTextScroll(true);
    HAL::GetCanvas()->setTextColor(TFT_BLUE, TFT_BLACK);

    // HAL::GetCanvas()->fillSmoothRoundRect(30, 20, 70, 40, 10, TFT_WHITE);
    HAL::GetCanvas()->fillRoundRect(30, 20, 70, 40, 10, TFT_WHITE);

    HAL::CanvasUpdate();
}

// Like loop()...
void AppLauncher::onRunning()
{
    static int shit = 0;
    shit++;
    HAL::GetCanvas()->printf("%d", shit);
    HAL::CanvasUpdate();
    HAL::Delay(20);
}

void AppLauncher::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());

    // Release resources here..
    // delete 114514;
}
