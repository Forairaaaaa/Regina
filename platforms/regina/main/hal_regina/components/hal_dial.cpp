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
#include <thread>
#include <mutex>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class TwoDials
{
private:
    struct DialData_t
    {
        uint8_t last_value = 0;
        uint8_t new_value = 0;
        int16_t count = 0;
        bool pin_swaped = false;
    };

    struct Data_t
    {
        DialData_t dial_a;
        DialData_t dial_b;

        uint16_t sample_count = 0;
        uint16_t sample_result = 0;
        std::array<uint16_t, 3> sample;
    };
    Data_t _data;

    void _pin_low(uint8_t pin) { gpio_set_level((gpio_num_t)pin, 0); }
    void _pin_high(uint8_t pin) { gpio_set_level((gpio_num_t)pin, 1); }
    int _pin_read(uint8_t pin) { return gpio_get_level((gpio_num_t)pin); }

    void _update_raw_value()
    {
        // Read data from p2s shift reg
        _pin_high(HAL_PIN_DIAL_CE);
        _pin_low(HAL_PIN_DIAL_PL);
        m5gfx::delayMicroseconds(5);
        _pin_high(HAL_PIN_DIAL_PL);
        _pin_low(HAL_PIN_DIAL_CE);

        _data.sample[_data.sample_count] = 0;
        for (uint8_t i = 0; i < 8; i++)
        {
            uint16_t value = _pin_read(HAL_PIN_DIAL_DATA);
            _data.sample[_data.sample_count] |= (value << ((8 - 1) - i));
            _pin_high(HAL_PIN_DIAL_CLK);
            m5gfx::delayMicroseconds(5);
            _pin_low(HAL_PIN_DIAL_CLK);
        }
    }

    void _update_sample_result()
    {
        std::unordered_map<uint16_t, int> frequency_map;
        for (uint16_t value : _data.sample)
        {
            frequency_map[value]++;
        }

        int max_count = 0;
        for (const auto& [value, count] : frequency_map)
        {
            if (count > max_count)
            {
                max_count = count;
                _data.sample_result = value;
            }
        }
    }

    void _pin_swaped_calibration(uint8_t& value) const
    {
        // 如果焊反了, swap bit0 and bit1, bit2 and bit3
        uint8_t temp = (value & 0b00001010) >> 1;
        value = (value & 0b00000101) << 1;
        value |= temp;
    }

    void _update_dial_value()
    {
        // Split into individual dial value
        _data.dial_a.new_value = (_data.sample_result & 0x0F);
        _data.dial_b.new_value = (_data.sample_result & 0xF0) >> 4;

        if (_data.dial_a.pin_swaped)
            _pin_swaped_calibration(_data.dial_a.new_value);
        if (_data.dial_b.pin_swaped)
            _pin_swaped_calibration(_data.dial_b.new_value);

        // spdlog::info("{} {}", _data.dial_a.new_value, _data.dial_b.new_value);
    }

    void _update_increment_counting(DialData_t& data) const
    {
        // Compare, get count and direction
        if (data.new_value != data.last_value)
        {
            int increment = data.new_value - data.last_value;

            // If equals 15 or -15 means overstep (0->15 or 15->0)
            // revert direction and get real increment
            if (increment == 15)
            {
                increment -= 16;
            }
            else if (increment == -15)
            {
                increment += 16;
            }

            // <BUG> There's trash data during overstep, seems no way to avoid it
            // Which produces a little wrong direction at that moment
            if (increment > 1)
                increment = 1;
            else if (increment < -1)
                increment = -1;

            // Apply to counting
            data.count += increment;
            data.last_value = data.new_value;
        }
    }

public:
    inline void setDialAPinSwaped(bool pinSwaped) { _data.dial_a.pin_swaped = pinSwaped; }
    inline const uint8_t& getDialAValue() { return _data.dial_a.new_value; }
    inline const int16_t& getDialACount() { return _data.dial_a.count; }
    inline void resetDialACount() { _data.dial_a.count = 0; }

    inline void setDialBPinSwaped(bool pinSwaped) { _data.dial_b.pin_swaped = pinSwaped; }
    inline const uint8_t& getDialBValue() { return _data.dial_b.new_value; }
    inline const int16_t& getDialBCount() { return _data.dial_b.count; }
    inline void resetDialBCount() { _data.dial_b.count = 0; }

    void init()
    {
        // Init pins
        std::vector<uint8_t> pin_list = {HAL_PIN_DIAL_CE, HAL_PIN_DIAL_CLK, HAL_PIN_DIAL_PL};
        for (const auto& i : pin_list)
        {
            gpio_reset_pin((gpio_num_t)i);
            gpio_set_direction((gpio_num_t)i, GPIO_MODE_OUTPUT);
        }

        gpio_reset_pin((gpio_num_t)HAL_PIN_DIAL_DATA);
        gpio_set_direction((gpio_num_t)HAL_PIN_DIAL_DATA, GPIO_MODE_INPUT);

        // Reset
        update();
        resetDialACount();
        resetDialBCount();

        // Init sample
        _data.sample_count = 0;
    }

    void update()
    {
        // Downsampling
        _update_raw_value();
        _data.sample_count++;
        if (_data.sample_count >= _data.sample.size())
        {
            _data.sample_count = 0;
            _update_sample_result();

            _update_dial_value();
            _update_increment_counting(_data.dial_a);
            _update_increment_counting(_data.dial_b);
        }
    }
};

static TwoDials* _dials = nullptr;
static std::mutex* _mutex = nullptr;

static void _dials_daemon(void* param)
{
    while (1)
    {
        _mutex->lock();
        _dials->update();
        _mutex->unlock();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}

void HAL_Regina::_dial_init()
{
    spdlog::info("dial init");

    _dials = new TwoDials;

    // Apply config
    _dials->setDialAPinSwaped(_data.config.dialAPinSwaped);
    _dials->setDialBPinSwaped(_data.config.dialBPinSwaped);
    _dials->init();

    spdlog::info("create daemon");
    _mutex = new std::mutex;
    // This shit works with test, but crash in app layer 😅
    // std::thread daemon(_dials_daemon);
    xTaskCreate(_dials_daemon, "dials", 2048, NULL, 5, NULL);

    /* -------------------------------------------------------------------------- */
    /*                                    Test                                    */
    /* -------------------------------------------------------------------------- */
    // while (1)
    // {
    //     _dials->update();
    //     delay(20);

    //     spdlog::info(" {} {} | {} {}",
    //                  _dials->getDialACount(),
    //                  _dials->getDialAValue(),
    //                  _dials->getDialBCount(),
    //                  _dials->getDialBValue());
    // }

    // while (1)
    // {
    //     delay(50);
    //     spdlog::info(" {} {} | {} {}",
    //                  getDialValue(DIAL::DIAL_A),
    //                  getDialCount(DIAL::DIAL_A),
    //                  getDialValue(DIAL::DIAL_B),
    //                  getDialCount(DIAL::DIAL_B));

    //     if (getAnyButton())
    //     {
    //         resetDialCount(DIAL::DIAL_A);
    //         resetDialCount(DIAL::DIAL_B);
    //     }
    // }
}

uint8_t HAL_Regina::getDialValue(DIAL::DialId_t dialId)
{
    int value = 0;
    _mutex->lock();

    if (dialId == DIAL::DIAL_A)
        value = _dials->getDialAValue();
    else if (dialId == DIAL::DIAL_B)
        value = _dials->getDialBValue();

    _mutex->unlock();
    return value;
}

int16_t HAL_Regina::getDialCount(DIAL::DialId_t dialId)
{
    int16_t count = 0;
    _mutex->lock();

    if (dialId == DIAL::DIAL_A)
        count = _dials->getDialACount();
    else if (dialId == DIAL::DIAL_B)
        count = _dials->getDialBCount();

    _mutex->unlock();
    return count;
}

void HAL_Regina::resetDialCount(DIAL::DialId_t dialId)
{
    _mutex->lock();

    if (dialId == DIAL::DIAL_A)
        _dials->resetDialACount();
    else if (dialId == DIAL::DIAL_B)
        _dials->resetDialBCount();

    _mutex->unlock();
}
