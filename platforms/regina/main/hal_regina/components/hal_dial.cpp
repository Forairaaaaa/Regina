/**
 * @file hal_dial.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_regina.h"
#include "../hal_config.h"
#include <mooncake.h>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

class TwoDials
{
private:
    struct DialData_t
    {
        uint8_t last_value = 0;
        uint8_t new_value = 0;
        int count = 0;
        int direction = 0;
    };

    struct Data_t
    {
        uint8_t raw_value = 0;
        DialData_t dial_a;
        DialData_t dial_b;
    };
    Data_t _data;

    void _pin_low(uint8_t pin) { gpio_set_level((gpio_num_t)pin, 0); }
    void _pin_high(uint8_t pin) { gpio_set_level((gpio_num_t)pin, 1); }
    int _pin_read(uint8_t pin) { return gpio_get_level((gpio_num_t)pin); }

    void _get_raw_value()
    {
        _pin_high(HAL_PIN_DIAL_CE);
        _pin_low(HAL_PIN_DIAL_PL);
        m5gfx::delayMicroseconds(5);
        _pin_high(HAL_PIN_DIAL_PL);
        _pin_low(HAL_PIN_DIAL_CE);

        _data.raw_value = 0;
        for (uint8_t i = 0; i < 8; i++)
        {
            uint8_t value = _pin_read(HAL_PIN_DIAL_DATA);
            _data.raw_value |= (value << ((8 - 1) - i));
            _pin_high(HAL_PIN_DIAL_CLK);
            m5gfx::delayMicroseconds(5);
            _pin_low(HAL_PIN_DIAL_CLK);
        }
    }

public:
    void init()
    {
        std::vector<uint8_t> pin_list = {HAL_PIN_DIAL_CE, HAL_PIN_DIAL_CLK, HAL_PIN_DIAL_PL};
        for (const auto& i : pin_list)
        {
            gpio_reset_pin((gpio_num_t)i);
            gpio_set_direction((gpio_num_t)i, GPIO_MODE_OUTPUT);
        }

        gpio_reset_pin((gpio_num_t)HAL_PIN_DIAL_DATA);
        gpio_set_direction((gpio_num_t)HAL_PIN_DIAL_DATA, GPIO_MODE_INPUT);
    }

    void update()
    {
        _get_raw_value();

        _data.dial_a.new_value = (_data.raw_value & 0x0F);
        _data.dial_b.new_value = (_data.raw_value & 0xF0) >> 4;
        // spdlog::info("{} {}", _data.dial_a.new_value, _data.dial_b.new_value);

        // Compare and get count
        if (_data.dial_a.new_value != _data.dial_a.last_value)
        {
            // Increment
            int increment = _data.dial_a.new_value - _data.dial_a.last_value;
            _data.dial_a.direction = (increment > 0) ? 1 : -1;
            if (increment > 8)
            {
                _data.dial_a.direction = -_data.dial_a.direction;
                increment -= 16;
            }
            else if (increment < -8)
            {
                _data.dial_a.direction = -_data.dial_a.direction;
                increment += 16;
            }
            _data.dial_a.count += increment;
            _data.dial_a.last_value = _data.dial_a.new_value;
        }
        else
            _data.dial_a.direction = 0;

        spdlog::info("{} {} {}", _data.dial_a.new_value, _data.dial_a.count, _data.dial_a.direction);
    }
};

static TwoDials* _two_dials = nullptr;

// static void _two_dial_daemon(void* param)
// {
//     while (1)
//     {
//     }
//     vTaskDelete(NULL);
// }

void HAL_Regina::_dial_init()
{
    spdlog::info("dial init");

    _two_dials = new TwoDials;
    _two_dials->init();

    /* -------------------------------------------------------------------------- */
    /*                                    Test                                    */
    /* -------------------------------------------------------------------------- */
    while (1)
    {
        _two_dials->update();
        delay(50);
    }
}
