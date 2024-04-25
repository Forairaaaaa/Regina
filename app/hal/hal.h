/**
 * @file hal.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <functional>
#include <vector>
#ifndef ESP_PLATFORM
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>
#include <cstdint>
#include <iostream>
#include <string>
#include "utils/lgfx_fx/lgfx_fx.h"
#include "types.h"
#else
#include "utils/lgfx_fx/lgfx_fx.h"
#include <LovyanGFX.hpp>
#include "types.h"
#endif

/**
 * @brief Singleton like pattern to simplify hal's getter
 * 1) Inherit and override methods to create a specific hal
 * 2) Use HAL::Inject() to inject your hal
 * 3) Use HAL:Get() to get this hal wherever you want
 */
class HAL
{
private:
    static HAL* _hal;

public:
    /**
     * @brief Get HAL instance
     *
     * @return HAL*
     */
    static HAL* Get();

    /**
     * @brief Check if HAL is valid
     *
     * @return true
     * @return false
     */
    static bool Check();

    /**
     * @brief HAL injection, init() will be called here
     *
     * @param hal
     * @return true
     * @return false
     */
    static bool Inject(HAL* hal);

    /**
     * @brief Destroy HAL instance
     *
     */
    static void Destroy();

    /**
     * @brief Base class
     *
     */
public:
    HAL() {}
    virtual ~HAL() {}

    static std::string Type() { return Get()->type(); }
    virtual std::string type() { return "Base"; }

    static std::string Version() { return Get()->version(); }
    virtual std::string version() { return APP_VERSION; }

    static std::string CompileDate() { return Get()->compileDate(); }
    virtual std::string compileDate() { return __DATE__; }

    virtual void init() {}

    /**
     * @brief Components
     *
     */
protected:
    struct Data_t
    {
        LGFX_Device* display = nullptr;
        LGFX_SpriteFx* canvas = nullptr;
        time_t time_buffer;
        CONFIG::SystemConfig_t config;
        IMU::ImuData_t imu_data;
    };
    Data_t _data;

    /* -------------------------------------------------------------------------- */
    /*                                   Display                                  */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Display device
     *
     * @return LGFX_Device*
     */
    static LGFX_Device* GetDisplay() { return Get()->_data.display; }

    /**
     * @brief Full screen canvas (sprite)
     *
     * @return LGFX_SpriteFx*
     */
    static LGFX_SpriteFx* GetCanvas() { return Get()->_data.canvas; }

    /**
     * @brief Push framebuffer
     *
     */
    static void CanvasUpdate() { Get()->canvasUpdate(); }
    virtual void canvasUpdate() { GetCanvas()->pushSprite(0, 0); }

    /**
     * @brief Render fps panel
     *
     */
    static void RenderFpsPanel() { Get()->renderFpsPanel(); }
    virtual void renderFpsPanel();

    /**
     * @brief Pop error message and wait reboot
     *
     * @param msg
     */
    static void PopFatalError(std::string msg) { Get()->popFatalError(msg); }
    virtual void popFatalError(std::string msg);

    /**
     * @brief Pop warning message and wait continue
     *
     * @param msg
     */
    static void PopWarning(std::string msg) { Get()->popWarning(msg); }
    virtual void popWarning(std::string msg);

    /**
     * @brief Pop success message and wait continue
     *
     * @param msg
     */
    static void PopSuccess(std::string msg, bool showSuccessLabel = true) { Get()->popSuccess(msg, showSuccessLabel); }
    virtual void popSuccess(std::string msg, bool showSuccessLabel = true);

    /* -------------------------------------------------------------------------- */
    /*                                   System                                   */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Delay(ms)
     *
     * @param milliseconds
     */
    static void Delay(unsigned long milliseconds) { Get()->delay(milliseconds); }
    virtual void delay(unsigned long milliseconds) { lgfx::delay(milliseconds); }

    /**
     * @brief Get the number of milliseconds passed since boot
     *
     * @return unsigned long
     */
    static unsigned long Millis() { return Get()->millis(); }
    virtual unsigned long millis() { return lgfx::millis(); }

    /**
     * @brief Power off
     *
     */
    static void PowerOff() { Get()->powerOff(); }
    virtual void powerOff() {}

    /**
     * @brief Reboot
     *
     */
    static void Reboot() { Get()->reboot(); }
    virtual void reboot() {}

    /**
     * @brief Set RTC time
     *
     * @param dateTime
     */
    static void SetSystemTime(tm dateTime) { return Get()->setSystemTime(dateTime); }
    virtual void setSystemTime(tm dateTime) {}

    /**
     * @brief Get local time(wrap of localtime())
     *
     * @return tm*
     */
    static tm* GetLocalTime() { return Get()->getLocalTime(); }
    virtual tm* getLocalTime();

    /**
     * @brief Reset system watch dog
     *
     */
    static void FeedTheDog() { Get()->feedTheDog(); }
    virtual void feedTheDog() {}

    /* -------------------------------------------------------------------------- */
    /*                                     MSC                                    */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Start MSC mode to expose fs as a USB disk
     *
     */
    static void StartMscMode() { Get()->startMscMode(); }
    virtual void startMscMode() {}

    /**
     * @brief Stop MSC mode
     *
     */
    static void StopMscMode() { Get()->stopMscMode(); }
    virtual void stopMscMode() {}

    /* -------------------------------------------------------------------------- */
    /*                                System config                               */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Load system config from fs
     *
     */
    static void LoadSystemConfig() { Get()->loadSystemConfig(); }
    virtual void loadSystemConfig() {}

    /**
     * @brief Save system config to fs
     *
     */
    static void SaveSystemConfig() { Get()->saveSystemConfig(); }
    virtual void saveSystemConfig() {}

    /**
     * @brief Get system config
     *
     * @return CONFIG::SystemConfig_t&
     */
    static CONFIG::SystemConfig_t& GetSystemConfig() { return Get()->_data.config; }

    /**
     * @brief Set system config
     *
     * @param cfg
     */
    static void SetSystemConfig(CONFIG::SystemConfig_t cfg) { Get()->_data.config = cfg; }

    /**
     * @brief Apply system config to device
     *
     */
    static void ApplySystemConfig() { Get()->applySystemConfig(); }
    virtual void applySystemConfig() {}

    /* -------------------------------------------------------------------------- */
    /*                                   Buzzer                                   */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Buzzer beep
     *
     * @param frequency
     * @param duration
     */
    static void Beep(float frequency, uint32_t duration = 4294967295U) { Get()->beep(frequency, duration); }
    virtual void beep(float frequency, uint32_t duration) {}

    /**
     * @brief Stop buzzer beep
     *
     */
    static void BeepStop() { Get()->beepStop(); }
    virtual void beepStop() {}

    /* -------------------------------------------------------------------------- */
    /*                                   Gamepad                                  */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Get button state, 获取按键状态
     *
     * @param button
     * @return true Pressing, 按下
     * @return false Released, 松开
     */
    static bool GetButton(GAMEPAD::GamePadButton_t button) { return Get()->getButton(button); }
    virtual bool getButton(GAMEPAD::GamePadButton_t button) { return false; }

    /**
     * @brief Get any button state, 获取任意按键状态
     *
     * @return true Pressing, 按下
     * @return false Released, 松开
     */
    static bool GetAnyButton() { return Get()->getAnyButton(); }
    virtual bool getAnyButton();

    /* -------------------------------------------------------------------------- */
    /*                                   Encoder                                  */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Update encoder count
     *
     */
    static void UpdateEncoderCount() { Get()->updateEncoderCount(); }
    virtual void updateEncoderCount() {}

    /**
     * @brief Get encoder count
     *
     * @return int
     */
    static int GetEncoderCount() { return Get()->getEncoderCount(); }
    virtual int getEncoderCount() { return 0; }

    /**
     * @brief Reset encoder count
     *
     */
    static void ResetEncoderCount(int value = 0) { Get()->resetEncoderCount(value); }
    virtual void resetEncoderCount(int value) {}

    /* -------------------------------------------------------------------------- */
    /*                                  Touchpad                                  */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Update touch
     *
     */
    static void UpdateTouch() { Get()->updateTouch(); }
    virtual void updateTouch() {}

    /**
     * @brief Is touching
     *
     * @return int
     */
    static int IsTouching() { return Get()->isTouching(); }
    virtual bool isTouching() { return false; }

    /**
     * @brief Get touch point
     *
     * @return TOUCH::Point_t
     */
    static TOUCH::Point_t GetTouchPoint() { return Get()->getTouchPoint(); }
    virtual TOUCH::Point_t getTouchPoint() { return {-1, -1}; }

    /* -------------------------------------------------------------------------- */
    /*                                     IMU                                    */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Update IMU data, 刷新IMU数据
     *
     */
    static void UpdateImuData() { Get()->updateImuData(); }
    virtual void updateImuData() {}

    /**
     * @brief Get the Imu Data, 获取IMU数据
     *
     * @return const IMU::ImuData_t&
     */
    static const IMU::ImuData_t& GetImuData() { return Get()->getImuData(); }
    const IMU::ImuData_t& getImuData() { return _data.imu_data; }

    /* -------------------------------------------------------------------------- */
    /*                                   Network                                  */
    /* -------------------------------------------------------------------------- */
public:
    static bool CheckWifiConfig() { return Get()->checkWifiConfig(); }
    virtual bool checkWifiConfig();

    static bool ConnectWifi(OnLogPageRenderCallback_t onLogPageRender, bool reconnect = false)
    {
        return Get()->connectWifi(onLogPageRender, reconnect);
    }
    virtual bool connectWifi(OnLogPageRenderCallback_t onLogPageRender, bool reconnect) { return false; }

    /* -------------------------------------------------------------------------- */
    /*                                     OTA                                    */
    /* -------------------------------------------------------------------------- */
public:
    static OTA_UPGRADE::OtaInfo_t GetLatestFirmwareInfoViaOta(OnLogPageRenderCallback_t onLogPageRender)
    {
        return Get()->getLatestFirmwareInfoViaOta(onLogPageRender);
    }
    virtual OTA_UPGRADE::OtaInfo_t getLatestFirmwareInfoViaOta(OnLogPageRenderCallback_t onLogPageRender)
    {
        return OTA_UPGRADE::OtaInfo_t();
    }

    static bool UpgradeFirmwareViaOta(OnLogPageRenderCallback_t onLogPageRender, const std::string& firmwareUrl)
    {
        return Get()->upgradeFirmwareViaOta(onLogPageRender, firmwareUrl);
    }
    virtual bool upgradeFirmwareViaOta(OnLogPageRenderCallback_t onLogPageRender, const std::string& firmwareUrl)
    {
        return false;
    }
};
