/**
 * @file hal_gamepad.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/lovyan03/LovyanGFX/blob/master/examples/HowToUse/2_user_setting/2_user_setting.ino
 * @version 0.1
 * @date 2023-11-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../hal_regina.h"
#include "../hal_config.h"
#include <mooncake.h>
#include <lgfx/v1/panel/Panel_SSD1306.hpp>

class LGFX_Regina : public lgfx::LGFX_Device
{
    lgfx::Panel_SSD1306 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    // lgfx::Light_PWM _light_instance;

public:
    LGFX_Regina(bool highRefreshRate = true)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.pin_mosi = HAL_PIN_OLED_SDA;
            cfg.pin_miso = -1;
            cfg.pin_sclk = HAL_PIN_OLED_SCL;
            cfg.pin_dc = HAL_PIN_OLED_DC;

            if (highRefreshRate)
                cfg.freq_write = 80000000;
            else
                cfg.freq_write = 40000000;

            cfg.spi_3wire = false;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.invert = true;
            cfg.pin_cs = HAL_PIN_OLED_CS;
            cfg.pin_rst = HAL_PIN_OLED_RST;
            cfg.pin_busy = -1;
            cfg.panel_width = 128;
            cfg.panel_height = 64;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            // cfg.bus_shared   = true;

            _panel_instance.config(cfg);
        }
        // {
        //     auto cfg = _light_instance.config();

        //     cfg.pin_bl = HAL_PIN_LCD_BL;
        //     cfg.invert = false;
        //     cfg.freq = 44100;
        //     cfg.pwm_channel = 7;

        //     _light_instance.config(cfg);
        //     _panel_instance.setLight(&_light_instance);
        // }

        setPanel(&_panel_instance);
    }
};

void HAL_Regina::_disp_init()
{
    spdlog::info("display init");

    if (_data.display != nullptr)
    {
        spdlog::info("already inited");
        return;
    }

    _data.display = new LGFX_Regina(true);
    _data.display->init();

    _data.canvas = new LGFX_SpriteFx(_data.display);
    _data.canvas->createSprite(_data.display->width(), _data.display->height());
}
