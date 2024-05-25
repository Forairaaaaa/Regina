/**
 * @file hal_ble.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_regina.h"
#include "../hal_config.h"
#include <mooncake.h>
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <BLECharacteristic.h>
#include <ArduinoJson.h>
#include <shared/shared.h>
#include <assets/assets.h>

/* -------------------------------------------------------------------------- */
/*                                Input status                                */
/* -------------------------------------------------------------------------- */
class BleInputStatus_t : public BLECharacteristicCallbacks
{
private:
    struct Data_t
    {
        BLECharacteristic* pCharacteristic = nullptr;
        uint8_t* value_buffer = nullptr;
    };
    Data_t _data;

public:
    BleInputStatus_t(BLEService* pService, const char* uuid)
    {
        _data.pCharacteristic =
            pService->createCharacteristic(uuid, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
        _data.pCharacteristic->setCallbacks(this);
        _data.pCharacteristic->addDescriptor(new BLE2902());

        _data.value_buffer = new uint8_t[10];
    }
    ~BleInputStatus_t() { delete _data.value_buffer; }

    void updateInput(const BLE_KB::InputFrame_t& newInput)
    {
        _data.value_buffer[0] = newInput.btnA;
        _data.value_buffer[1] = newInput.btnB;
        _data.value_buffer[2] = newInput.btnC;
        _data.value_buffer[3] = newInput.btnD;
        _data.value_buffer[4] = newInput.valueDialA;
        _data.value_buffer[5] = newInput.valueDialB;

        // int16 by le
        _data.value_buffer[6] = newInput.countDialA & 0xFF;
        _data.value_buffer[7] = (newInput.countDialA >> 8) & 0xFF;
        _data.value_buffer[8] = newInput.countDialB & 0xFF;
        _data.value_buffer[9] = (newInput.countDialB >> 8) & 0xFF;

        // Update
        _data.pCharacteristic->setValue(_data.value_buffer, 10);
        _data.pCharacteristic->notify();
    }
};

/* -------------------------------------------------------------------------- */
/*                                     IMU                                    */
/* -------------------------------------------------------------------------- */
class BleImuData_t : public BLECharacteristicCallbacks
{
private:
    struct Data_t
    {
        BLECharacteristic* pCharacteristicAccel = nullptr;
        BLECharacteristic* pCharacteristicGyro = nullptr;
        uint8_t* value_buffer = nullptr;
    };
    Data_t _data;

public:
    BleImuData_t(BLEService* pService, const char* uuidAccel, const char* uuidGyro)
    {
        _data.pCharacteristicAccel =
            pService->createCharacteristic(uuidAccel, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
        _data.pCharacteristicAccel->setCallbacks(this);
        _data.pCharacteristicAccel->addDescriptor(new BLE2902());

        _data.pCharacteristicGyro =
            pService->createCharacteristic(uuidGyro, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
        _data.pCharacteristicGyro->setCallbacks(this);
        _data.pCharacteristicGyro->addDescriptor(new BLE2902());

        // 6 * 32 float = 24
        _data.value_buffer = new uint8_t[24];
    }
    ~BleImuData_t() { delete _data.value_buffer; }

    void updateImuData(const IMU::ImuData_t& newData)
    {
        // 6 float in le
        memcpy(_data.value_buffer, &newData.accel.x, sizeof(float));
        memcpy(_data.value_buffer + 4, &newData.accel.y, sizeof(float));
        memcpy(_data.value_buffer + 8, &newData.accel.z, sizeof(float));
        memcpy(_data.value_buffer + 12, &newData.gyro.x, sizeof(float));
        memcpy(_data.value_buffer + 16, &newData.gyro.y, sizeof(float));
        memcpy(_data.value_buffer + 20, &newData.gyro.z, sizeof(float));

        // Update
        _data.pCharacteristicAccel->setValue(_data.value_buffer, 12);
        _data.pCharacteristicAccel->notify();
        _data.pCharacteristicGyro->setValue(_data.value_buffer + 12, 12);
        _data.pCharacteristicGyro->notify();
    }
};

/* -------------------------------------------------------------------------- */
/*                                System config                               */
/* -------------------------------------------------------------------------- */
class BleSystemConfig_t : public BLECharacteristicCallbacks
{
private:
    struct Data_t
    {
        BLECharacteristic* pCharacteristic = nullptr;
    };
    Data_t _data;

public:
    BleSystemConfig_t(BLEService* pService, const char* uuid)
    {
        _data.pCharacteristic =
            pService->createCharacteristic(uuid, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
        _data.pCharacteristic->setCallbacks(this);
    }

    void onWrite(BLECharacteristic* pCharacteristic) override
    {
        std::string value = pCharacteristic->getValue().c_str();
        spdlog::info("syscfg get:\n {}", value);

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, value);
        if (error != DeserializationError::Ok)
        {
            spdlog::error("parse failed!");
            return;
        }

        if (!doc["mute"].isNull())
            HAL::GetSystemConfig().mute = doc["mute"];
        if (!doc["dialAPinSwaped"].isNull())
            HAL::GetSystemConfig().dialAPinSwaped = doc["dialAPinSwaped"];
        if (!doc["dialBPinSwaped"].isNull())
            HAL::GetSystemConfig().dialBPinSwaped = doc["dialBPinSwaped"];
        if (!doc["autoSleepTimeout"].isNull())
            HAL::GetSystemConfig().autoSleepTimeout = doc["autoSleepTimeout"];
        if (!doc["wifiSsid"].isNull())
            HAL::GetSystemConfig().wifiSsid = doc["wifiSsid"].as<std::string>();
        if (!doc["wifiPassword"].isNull())
            HAL::GetSystemConfig().wifiPassword = doc["wifiPassword"].as<std::string>();
        if (!doc["unixTimestamp"].isNull())
            timeConfig(doc["unixTimestamp"].as<std::string>());

        HAL::SaveSystemConfig();
    }

    void onRead(BLECharacteristic* pCharacteristic) override
    {
        auto json = HAL::GetSystemConfigJson();
        pCharacteristic->setValue(json.c_str());
    }

    void timeConfig(const std::string& unixTimestamp)
    {
        if (unixTimestamp.empty())
            return;

        spdlog::info("time config get: {}", unixTimestamp);

        long unix_time_stamp = atol(unixTimestamp.c_str());
        spdlog::info("unix stamp: {}", unix_time_stamp);

        struct tm* time_info;
        time_t timestamp_sec = unix_time_stamp;
        time_info = localtime(&timestamp_sec);

        {
            char string_buffer[80];
            strftime(string_buffer, sizeof(string_buffer), "%Y-%m-%d %H:%M:%S", time_info);
            spdlog::info("get time: {}", string_buffer);
        }

        HAL::SetSystemTime(*time_info);
    }
};

/* -------------------------------------------------------------------------- */
/*                                   Message                                  */
/* -------------------------------------------------------------------------- */
class BleMessage_t : public BLECharacteristicCallbacks
{
private:
    struct Data_t
    {
        BLECharacteristic* pCharacteristic = nullptr;
    };
    Data_t _data;

public:
    BleMessage_t(BLEService* pService, const char* uuid)
    {
        _data.pCharacteristic = pService->createCharacteristic(uuid, BLECharacteristic::PROPERTY_WRITE);
        _data.pCharacteristic->setCallbacks(this);
    }

    void onWrite(BLECharacteristic* pCharacteristic) override
    {
        std::string value = pCharacteristic->getValue().c_str();
        spdlog::info("message get:\n {}", value);

        SharedData::BorrowData();

        // Pipe in
        SharedData::Console().setEnable(true);
        SharedData::Console().log("{}", value);

        // Ring
        HAL::PlayRingtone();

        SharedData::ReturnData();
    }
};

/* -------------------------------------------------------------------------- */
/*                                   My Shit                                  */
/* -------------------------------------------------------------------------- */
class MyBleShit : public BLEServerCallbacks
{
private:
    struct Data_t
    {
        BleInputStatus_t* input = nullptr;
        BleImuData_t* imu = nullptr;
        BleSystemConfig_t* syscfg = nullptr;
        BleMessage_t* msg = nullptr;
        BLEAdvertising* pAdvertising = nullptr;
        bool is_connected = false;
    };
    Data_t _data;

public:
    MyBleShit() {}
    ~MyBleShit()
    {
        delete _data.input;
        delete _data.imu;
        delete _data.syscfg;
        delete _data.msg;
    }

    void init()
    {
        // Server
        BLEDevice::init("Reginaaaa:)");
        BLEServer* pServer = BLEDevice::createServer();
        pServer->setCallbacks(this);

        // Service
        BLEService* pService = pServer->createService("2333");
        _data.input = new BleInputStatus_t(pService, "2334");
        _data.imu = new BleImuData_t(pService, "2335", "2336");
        _data.syscfg = new BleSystemConfig_t(pService, "2337");
        _data.msg = new BleMessage_t(pService, "2338");

        // Start service
        pService->start();

        // Advertising
        _data.pAdvertising = pServer->getAdvertising();
        _data.pAdvertising->setAppearance(0x00C0);
        _data.pAdvertising->addServiceUUID(pService->getUUID());
        _data.pAdvertising->setScanResponse(false);
        _data.pAdvertising->start();
    }

    void onConnect(BLEServer* pServer) override
    {
        _data.is_connected = true;
        SharedData::BorrowData().console_msg_pipe.log("连接成功");
        SharedData::ReturnData();
    }

    void onDisconnect(BLEServer* pServer) override
    {
        _data.is_connected = false;
        SharedData::BorrowData().console_msg_pipe.log("连接断开:(");
        SharedData::ReturnData();

        _data.pAdvertising->start();
    }

    inline bool isConnected() { return _data.is_connected; }

    void updateInput(const BLE_KB::InputFrame_t& newInput) { _data.input->updateInput(newInput); }

    void updateImuDate(const IMU::ImuData_t& newData) { _data.imu->updateImuData(newData); }
};
static MyBleShit* _my_ble_shit = nullptr;

/* -------------------------------------------------------------------------- */
/*                                    APIs                                    */
/* -------------------------------------------------------------------------- */
void HAL_Regina::_ble_init()
{
    spdlog::info("ble init");

    assert(_my_ble_shit == nullptr);
    _my_ble_shit = new MyBleShit;
    _my_ble_shit->init();
}

bool HAL_Regina::isBleConnected()
{
    if (_my_ble_shit != nullptr)
        return _my_ble_shit->isConnected();
    return false;
}

void HAL_Regina::bleUpdateInput(const BLE_KB::InputFrame_t& newInput)
{
    if (_my_ble_shit == nullptr)
        return;
    _my_ble_shit->updateInput(newInput);
}

void HAL_Regina::bleUpdateImuData(const IMU::ImuData_t& newData)
{
    if (_my_ble_shit == nullptr)
        return;
    _my_ble_shit->updateImuDate(newData);
}
