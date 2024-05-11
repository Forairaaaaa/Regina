/**
 * @file app_settings.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_settings.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../utils/system/system.h"
#include "lgfx/v1/misc/enum.hpp"

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppSettings_Packer::getAppName() { return "AppSettings"; }

// Icon
void* AppSettings_Packer::getAppIcon() { return nullptr; }

// Like setup()...
void AppSettings::onResume()
{
    spdlog::info("{} onResume", getAppName());

    HAL::GetCanvas()->fillScreen(TFT_BLACK);
    AssetPool::LoadFont12(HAL::GetCanvas());
    HAL::GetCanvas()->setCursor(0, 0);
    HAL::GetCanvas()->print("啊?");
    HAL::CanvasUpdate();
}

// Like loop()...
void AppSettings::onRunning()
{
    // Print hi in every 1s
    if (HAL::Millis() - _data.time_count > 1000)
    {
        spdlog::info("Hi");
        _data.time_count = HAL::Millis();
    }

    // Update button state
    Button::Update();

    // Handle encoder button click
    if (Button::A()->wasClicked())
        spdlog::info("encoder button clicked");

    // Check quit
    if (Button::A()->isHolding())
        destroyApp();

    // ...
    // If you want to block here, feed the dog manually
    // HAL::FeedTheDog();
}

void AppSettings::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());

    // Release resources here..
    // delete 114514;
}
