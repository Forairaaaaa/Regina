/**
 * @file hal_i2c.cpp
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
#include <Arduino.h>

void HAL_Regina::_i2c_init()
{
    spdlog::info("i2c bus init");

    // Init
    _i2c_bus = new m5::I2C_Class;
    _i2c_bus->begin(I2C_NUM_0, HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL);

    // Scan
    spdlog::info("start scan:");
    bool scan_list[120];
    _i2c_bus->scanID(scan_list);
    uint8_t device_num = 0;
    for (int i = 8; i < 0x78; i++)
    {
        if (scan_list[i])
        {
            device_num++;
            spdlog::info("get 0x{0:x}", i);
        }
    }
    spdlog::info("device num: {}", device_num);
}
