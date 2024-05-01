/**
 * @file hal_desktop.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <mooncake.h>
#include <M5GFX.h>
#include "LGFX_AutoDetect_sdl.hpp"
#include <hal/hal.h>
#include <cmath>
#include <string>
#include <vector>
#include <random>

class HAL_Desktop : public HAL
{
private:
    int _screenWidth;
    int _screenHeight;
    bool _zoom;

public:
    std::string type() override { return "Desktop"; }

    HAL_Desktop(int screenWidth = 240, int screenHeight = 240, bool zoom = false)
        : _screenWidth(screenWidth), _screenHeight(screenHeight), _zoom(zoom)
    {
    }

    void init() override
    {
        // Display
        if (_zoom)
            _data.display = new LGFX(_screenWidth * 2, _screenHeight * 2);
        else
            _data.display = new LGFX(_screenWidth, _screenHeight);

        _data.display->init();

        // Canvas
        _data.canvas = new LGFX_SpriteFx(_data.display);
        _data.canvas->createSprite(_screenWidth, _screenHeight);
        _data.canvas->setColorDepth(1);
        // _data.canvas->setColorDepth(lgfx::color_depth_t::grayscale_1bit);

        // Some pc window pop up slower?
        // lgfx::delay(1500);
        lgfx::delay(500);

        // this->popWarning("404 not found\nasdasd asdfasf");
        // this->popSuccess("404 not found\nasdasd asdfasf");
        // this->popFatalError("404 not found\nasdasd asdfasf");

        _data.config.wifiSsid = "114514";
        _data.config.wifiPassword = "1919810";
    }

    void canvasUpdate() override
    {
        if (_zoom)
            GetCanvas()->pushRotateZoom(_data.display, 129, 65, 0, 2, 2);
        else
            GetCanvas()->pushSprite(0, 0);
    }

    bool getButton(GAMEPAD::GamePadButton_t button) override
    {
        if (button == GAMEPAD::BTN_A)
            return !lgfx::gpio_in(39);
        else if (button == GAMEPAD::BTN_B)
            return !lgfx::gpio_in(37);
        else if (button == GAMEPAD::BTN_PWR)
            return !lgfx::gpio_in(38);
        else if (button == GAMEPAD::BTN_C)
            return !lgfx::gpio_in(39);
        else if (button == GAMEPAD::BTN_D)
            return !lgfx::gpio_in(37);

        return false;
    }

    // Simulate encoder by mouse drag
    int encoder_count = 0;
    int last_encoder_count = 0;
    int touch_start_x = 0;
    int touch_last_x = 0;
    bool is_touching = false;
    int getEncoderCount() override
    {
        if (isTouching())
        {
            if (!is_touching)
            {
                is_touching = true;
                touch_start_x = getTouchPoint().x;
                return encoder_count;
            }

            if (getTouchPoint().x != touch_last_x)
            {
                // spdlog::info("{} {} {}", touch_start_x, getTouchPoint().x, encoder_count);
                encoder_count = (getTouchPoint().x - touch_start_x) / 20 + last_encoder_count;
            }
            touch_last_x = getTouchPoint().x;
        }
        else if (is_touching)
        {
            is_touching = false;
            last_encoder_count = encoder_count;
        }

        // // Reverse
        return -encoder_count;
        // // return encoder_count;

        // if (_data.config.reverseEncoder)
        //     return encoder_count;
        // return -encoder_count;
    }

    void resetEncoderCount(int value) override { encoder_count = value; }

    bool isTouching() override
    {
        lgfx::touch_point_t tp;
        _data.display->getTouch(&tp);
        // spdlog::info("{} {} {}", tp.x, tp.y, tp.size);
        return tp.size != 0;
    }

    TOUCH::Point_t getTouchPoint() override
    {
        lgfx::touch_point_t tp;
        _data.display->getTouch(&tp);
        return {tp.x, tp.y};
    }

    float generateRandomNumber(float v1, float v2)
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_real_distribution<float> distribution(v1, v2);
        return distribution(generator);
    }

    bool connectWifi(OnLogPageRenderCallback_t onLogPageRender, bool reconnect) override
    {
        onLogPageRender(" connecting wifi..\n", true, true);
        delay(300);
        return true;
    }

    OTA_UPGRADE::OtaInfo_t getLatestFirmwareInfoViaOta(OnLogPageRenderCallback_t onLogPageRender) override
    {
        OTA_UPGRADE::OtaInfo_t info;
        info.firmwareUrl = "www.114514.com";
        info.latestVersion = "V6.6.6";
        info.upgradeAvailable = true;
        return info;
    }

    bool upgradeFirmwareViaOta(OnLogPageRenderCallback_t onLogPageRender, const std::string& firmwareUrl) override
    {
        onLogPageRender(" connecting wifi..\n", true, false);
        delay(200);

        onLogPageRender(" upgrading..\n", true, false);
        delay(200);

        for (int i = 0; i < 100; i += 5)
        {
            std::string log = "<PB>";
            log += std::to_string(i);
            log += "\n";
            onLogPageRender(log, true, false);
            delay(100);
        }

        onLogPageRender(" done\n", true, true);
        delay(200);

        popSuccess("Upgrade done");
        return true;
    }

    uint8_t getBatteryPercentage() override { return 100; }
};
