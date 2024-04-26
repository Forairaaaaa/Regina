/**
 * @file hal_regina.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <hal/hal.h>

class HAL_Regina : public HAL
{
private:
    void _watch_dog_init();
    void _disp_init();
    void _gamepad_init();
    void _dial_init();
    void _seaker_init();

    void _i2c_init();
    void _rtc_init();
    void _adjust_sys_time();
    void _imu_init();
    void _pmu_init();

    void _fs_init();
    std::vector<std::string> _ls(const std::string& path);
    void _config_check_valid();
    void _log_out_system_config();

    // std::string _get_mac();

public:
    std::string type() override { return "Regina"; }

    inline void init() override
    {
        _gamepad_init();
        _dial_init();
        _watch_dog_init();
        _fs_init();
        _disp_init();
        _seaker_init();
        _i2c_init();
        _rtc_init();
        _imu_init();
        _pmu_init();
    }

    /* -------------------------------------------------------------------------- */
    /*                             Public api override                            */
    /* -------------------------------------------------------------------------- */
    void reboot() override;
    void powerOff() override;
    uint8_t getBatteryPercentage() override;
    bool isBatteryCharging() override;

    void feedTheDog() override;
    bool getButton(GAMEPAD::GamePadButton_t button) override;
    void setSystemTime(tm dateTime) override;
    void updateImuData() override;
    void beep(float frequency, uint32_t duration) override;
    void beepStop() override;

    void loadSystemConfig() override;
    void saveSystemConfig() override;
};
