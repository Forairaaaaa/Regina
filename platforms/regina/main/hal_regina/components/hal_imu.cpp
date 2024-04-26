/**
 * @file hal_imu.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/m5stack/M5Unified
 * @version 0.1
 * @date 2023-11-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <mooncake.h>
#include "../hal_regina.h"
#include "../hal_config.h"

// #include <lgfx/boards.hpp>
// namespace m5
// {
//     using board_t = m5gfx::board_t;
// }
// #include <utility/IMU_Class.hpp>
#include <utility/imu/BMI270_Class.hpp>

class My_BMI270_Class : public m5::BMI270_Class
{
public:
    My_BMI270_Class(std::uint8_t i2c_addr = 0x68, std::uint32_t freq = 400000, m5::I2C_Class* i2c = &m5::In_I2C)
        : m5::BMI270_Class(i2c_addr, freq, i2c)
    {
    }

    bool getAccel(float* ax, float* ay, float* az)
    {
        static constexpr float aRes = 8.0f / 32768.0f;
        std::int16_t buf[3];
        bool res = readRegister(ACC_X_LSB_ADDR, (std::uint8_t*)buf, 6);
        *ax = buf[0] * aRes;
        *ay = buf[1] * aRes;
        *az = buf[2] * aRes;
        return res;
    }

    bool getGyro(float* gx, float* gy, float* gz)
    {
        static constexpr float gRes = 2000.0f / 32768.0f;
        std::int16_t buf[3];
        bool res = readRegister(GYR_X_LSB_ADDR, (std::uint8_t*)buf, 6);
        *gx = buf[0] * gRes;
        *gy = buf[1] * gRes;
        *gz = buf[2] * gRes;
        return res;
    }

    bool getTemp(float* t)
    {
        std::int16_t buf;
        bool res = readRegister(TEMPERATURE_0_ADDR, (std::uint8_t*)&buf, 2);
        *t = 23.0f + buf / 512.0f;
        return res;
    }
};

static My_BMI270_Class* _imu = nullptr;

void HAL_Regina::_imu_init()
{
    spdlog::info("imu init");

    _imu = new My_BMI270_Class;
    if (!_imu->begin(&m5::In_I2C))
    {
        spdlog::error("init failed!");
        delete _imu;
    }

    // /* -------------------------------------------------------------------------- */
    // /*                                    Test                                    */
    // /* -------------------------------------------------------------------------- */
    // while (1)
    // {
    //     updateImuData();
    //     spdlog::info("{:.6f} {:.6f} {:.6f} {:.6f} {:.6f} {:.6f}",
    //                  getImuData().accel.x,
    //                  getImuData().accel.y,
    //                  getImuData().accel.z,
    //                  getImuData().gyro.x,
    //                  getImuData().gyro.y,
    //                  getImuData().gyro.z);
    //     delay(100);
    // }
}

void HAL_Regina::updateImuData()
{
    if (_imu == nullptr)
        return;

    _imu->getAccel(&_data.imu_data.accel.x, &_data.imu_data.accel.y, &_data.imu_data.accel.z);
    _imu->getGyro(&_data.imu_data.gyro.x, &_data.imu_data.gyro.y, &_data.imu_data.gyro.z);
}
