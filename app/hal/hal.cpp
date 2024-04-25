/**
 * @file hal.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "hal.h"
#include <mooncake.h>
#include "../assets/assets.h"
#include <sstream>

HAL* HAL::_hal = nullptr;

HAL* HAL::Get() { return _hal; }

bool HAL::Check() { return _hal != nullptr; }

bool HAL::Inject(HAL* hal)
{
    if (_hal != nullptr)
    {
        spdlog::error("HAL already exist");
        return false;
    }

    if (hal == nullptr)
    {
        spdlog::error("invalid HAL ptr");
        return false;
    }

    hal->init();
    spdlog::info("HAL injected, type: {}", hal->type());

    _hal = hal;

    return true;
}

void HAL::Destroy()
{
    if (_hal == nullptr)
    {
        spdlog::error("HAL not exist");
        return;
    }

    delete _hal;
    _hal = nullptr;
}

void HAL::renderFpsPanel()
{
    static unsigned long time_count = 0;

    _data.canvas->setTextColor(TFT_WHITE, TFT_BLACK);
    _data.canvas->setTextSize(1);
    _data.canvas->setTextDatum(top_left);
    _data.canvas->drawNumber(1000 / (millis() - time_count), 0, 0, &fonts::Font0);
    // _data.canvas->drawNumber(123, 0, 0, &fonts::Font0);

    time_count = millis();
}

static constexpr int _msg_start_x = 16;
static constexpr int _msg_start_y = 130;
static constexpr int _msg_line_height = 32;

void HAL::popFatalError(std::string msg)
{
    // // Echo
    // spdlog::error("{}", msg);

    // /* ---------------------------------- Face ---------------------------------- */
    // _data.canvas->setTextColor(TFT_WHITE, AssetPool::GetColor().Misc.bgPopFatalError);
    // _data.canvas->fillScreen(AssetPool::GetColor().Misc.bgPopFatalError);

    // _data.canvas->setTextSize(1);
    // _data.canvas->setTextDatum(top_left);
    // _data.canvas->loadFont(AssetPool::GetStaticAsset()->Font.montserrat_semibolditalic_72);
    // _data.canvas->setCursor(20, 10);
    // _data.canvas->printf(":(");

    // /* ----------------------------------- Msg ---------------------------------- */
    // int line_height = _msg_start_y;
    // AssetPool::LoadFont24(_data.canvas);
    // _data.canvas->setCursor(_msg_start_x, line_height);
    // _data.canvas->printf("Fatal Error!");

    // std::istringstream msg_stream(msg);
    // std::string line;
    // while (std::getline(msg_stream, line))
    // {
    //     line_height += _msg_line_height;
    //     _data.canvas->setCursor(_msg_start_x, line_height);
    //     _data.canvas->print(line.c_str());
    // }

    // /* ---------------------------------- Push ---------------------------------- */
    // _data.canvas->pushSprite(0, 0);
    // _data.display->setBrightness(255);

    // // Press any button to poweroff
    // while (1)
    // {
    //     feedTheDog();
    //     delay(50);

    //     if (getAnyButton())
    //         reboot();
    // }
}

void HAL::popWarning(std::string msg) {}

void HAL::popSuccess(std::string msg, bool showSuccessLabel) {}

// Cpp sucks
tm* HAL::getLocalTime()
{
    time(&_data.time_buffer);
    return localtime(&_data.time_buffer);
}

bool HAL::getAnyButton()
{
    for (int i = GAMEPAD::BTN_START; i < GAMEPAD::GAMEPAD_BUTTON_NUM; i++)
    {
        if (getButton(static_cast<GAMEPAD::GamePadButton_t>(i)))
            return true;
    }
    return false;
}

bool HAL::checkWifiConfig()
{
    if (_data.config.wifiSsid.empty())
    {
        popWarning("WiFi SSID is empty");
        return false;
    }

    if (_data.config.wifiPassword.empty())
    {
        popWarning("WiFi Password is empty");
        return false;
    }

    return true;
}
