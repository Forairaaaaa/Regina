/**
 * @file hal_pmu.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 */
// ref: https://github.com/HwzLoveDz/AXP202-PMIC/tree/main
#include <mooncake.h>
#include "../hal_regina.h"
#include "../hal_config.h"
#include <utility/I2C_Class.hpp>

class AXP202_Class : public m5::I2C_Device
{
public:
    AXP202_Class(std::uint8_t i2c_addr = 0x34, std::uint32_t freq = 400000, m5::I2C_Class* i2c = &m5::In_I2C)
        : I2C_Device(i2c_addr, freq, i2c)
    {
    }

    bool begin()
    {
        auto id = readRegister8(0x03);
        spdlog::info("get id 0x{0:x}", id);
        if (id != 0x41)
            return false;
        return true;
    }

    void powerOff()
    {
        const uint8_t reg = 0x32;
        auto val = readRegister8(reg);
        val |= (1 << 7);
        writeRegister8(reg, val);
    }

    uint8_t batteryPercentage()
    {
        const uint8_t reg = 0xB9;
        auto val = readRegister8(reg);
        val &= 0x01111111;
        return val;
    }

    bool isCharging()
    {
        const uint8_t reg = 0x01;
        auto val = readRegister8(reg);
        val &= 0x01000000;
        return (bool)val;
    }
};

static AXP202_Class* _pmu = nullptr;

void HAL_Regina::_pmu_init()
{
    spdlog::info("pmu init");

    _pmu = new AXP202_Class;
    if (!_pmu->begin())
    {
        spdlog::error("init failed!");
        delete _pmu;
    }

    // /* -------------------------------------------------------------------------- */
    // /*                                    Test                                    */
    // /* -------------------------------------------------------------------------- */
    // int shit = 0;
    // while (shit < (10000 / 500))
    // {
    //     shit++;
    //     spdlog::info("{} {}", getBatteryPercentage(), isBatteryCharging());
    //     delay(500);
    // }
    // powerOff();
}

void HAL_Regina::reboot() { esp_restart(); }

void HAL_Regina::powerOff()
{
    if (_pmu == nullptr)
        return;
    _pmu->powerOff();
    while (1)
        delay(1000);
}

uint8_t HAL_Regina::getBatteryPercentage()
{
    if (_pmu == nullptr)
        return 0;
    return _pmu->batteryPercentage();
}

bool HAL_Regina::isBatteryCharging()
{
    if (_pmu == nullptr)
        return false;
    return _pmu->isCharging();
}
