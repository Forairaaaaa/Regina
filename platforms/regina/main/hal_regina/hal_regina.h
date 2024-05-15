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
    // void _mic_init();

    void _i2c_init();
    void _rtc_init();
    void _adjust_sys_time();
    void _imu_init();
    void _pmu_init();

    void _fs_init();
    std::vector<std::string> _ls(const std::string& path);
    void _config_check_valid();
    void _log_out_system_config();
    std::string _create_config_json();

    // std::string _get_mac();

    void _ble_init();

public:
    std::string type() override { return "Regina"; }

    inline void init() override
    {
        _gamepad_init();
        _watch_dog_init();
        _fs_init();
        _disp_init();
        _seaker_init();
        // _mic_init();
        _i2c_init();
        _rtc_init();
        _imu_init();
        _pmu_init();
        _dial_init();
        _ble_init();
    }

    /* -------------------------------------------------------------------------- */
    /*                             Public api override                            */
    /* -------------------------------------------------------------------------- */
    void reboot() override;
    void powerOff() override;
    uint8_t getBatteryPercentage() override;
    bool isBatteryCharging() override;
    bool wasPowerButtonClicked() override;

    void feedTheDog() override;
    void setSystemTime(tm dateTime) override;

    bool getButton(GAMEPAD::GamePadButton_t button) override;
    void updateImuData() override;
    void beep(float frequency, uint32_t duration) override;
    void beepStop() override;
    uint8_t getDialValue(DIAL::DialId_t dialId) override;
    int getDialCount(DIAL::DialId_t dialId) override;
    void resetDialCount(DIAL::DialId_t dialId) override;

    void loadSystemConfig() override;
    void saveSystemConfig() override;
    inline std::string getSystemConfigJson() override { return _create_config_json(); }

    bool isBleConnected() override;
    size_t bleKeyBoardWrite(const uint8_t c) override;
    size_t bleKeyBoardWrite(const BLE_KB::MediaKeyReport c) override;
    void bleUpdateInput(const BLE_KB::InputFrame_t& newInput) override;
};
