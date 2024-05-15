/**
 * @file shared.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>
#include <functional>
#include <queue>
#include <vector>
#include "types.h"

/**
 * @brief Provide a singleton for sharing dynamic data between apps(or layers, not recommend)
 *
 */
class SharedData
{
private:
    static SharedData* _shared_data;

public:
    /**
     * @brief Get SharedData instance
     *
     * @return SharedData*
     */
    static SharedData* Get();

    /**
     * @brief Check if SharedData is valid
     *
     * @return true
     * @return false
     */
    static bool Check();

    /**
     * @brief SharedData injection
     *
     * @param sharedData
     * @return true
     * @return false
     */
    static bool Inject(SharedData* sharedData);

    /**
     * @brief Destroy SharedData instance
     *
     */
    static void Destroy();

    /**
     * @brief Sharing data
     *
     */
private:
    SHARED_DATA::SharedData_t _data;

    /**
     * @brief Base class
     *
     */
public:
    SharedData() {}
    virtual ~SharedData() {}

    static std::string Type() { return Get()->type(); }
    virtual std::string type() { return "Base"; }

    /**
     * @brief Get data directly
     *
     * @return SHARED_DATA::SharedData_t&
     */
    static SHARED_DATA::SharedData_t& GetData() { return Get()->getData(); }
    virtual SHARED_DATA::SharedData_t& getData() { return _data; }

    /**
     * @brief Borrow data, override to lock mutex or whatever
     *
     * @return SHARED_DATA::SharedData_t&
     */
    static SHARED_DATA::SharedData_t& BorrowData() { return Get()->borrowData(); }
    virtual SHARED_DATA::SharedData_t& borrowData() { return _data; }

    /**
     * @brief Borrow data, override to unlock mutex or whatever
     *
     */
    static void ReturnData() { Get()->returnData(); }
    virtual void returnData() {}

    /* -------------------------------------------------------------------------- */
    /*                               Helper getters                               */
    /* -------------------------------------------------------------------------- */
public:
    static std::string AppVersion() { return Get()->appVersion(); }
    virtual std::string appVersion() { return APP_VERSION; }

    /* -------------------------------------------------------------------------- */
    /*                                   Console                                  */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Small terminal canvas
     *
     * @return LGFX_SpriteFx*
     */
    static LGFX_SpriteFx* GetConsoleCanvas() { return GetData().console_canvas; }
    static void SetConsoleCanvas(LGFX_SpriteFx* terminalCanvas) { GetData().console_canvas = terminalCanvas; }

    /**
     * @brief Get console message pipe line
     *
     * @return CONSOLE::ConsolePipe_t&
     */
    static CONSOLE::ConsolePipe_t& Console() { return GetData().console_msg_pipe; }

    /* -------------------------------------------------------------------------- */
    /*                                    Power                                   */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Get current power state
     *
     * @return POWER::PowerState_t
     */
    static POWER::PowerState_t GetPowerState() { return GetData().power_state; }

    /**
     * @brief Set power state
     *
     * @param state
     */
    static void SetPowerState(POWER::PowerState_t state) { GetData().power_state = state; }

    /**
     * @brief Reset auto sleep counting
     *
     * @param coffee
     */
    static void CupOfCoffee(const uint32_t coffee) { GetData().awake_time_count = coffee; }

    /**
     * @brief Get awake time count
     *
     * @return uint32_t
     */
    static uint32_t GetAwakeTime() { return GetData().awake_time_count; }

    /* -------------------------------------------------------------------------- */
    /*                                Notification                                */
    /* -------------------------------------------------------------------------- */
public:
    /**
     * @brief Get notification pipe
     *
     * @return std::queue<NOTIF::Notification_t>&
     */
    std::queue<NOTIF::Notification_t>& GetNotificationPipe() { return GetData().notification_pipe; }
};
