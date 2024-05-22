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

/* -------------------------------------------------------------------------- */
/*                                Input status                                */
/* -------------------------------------------------------------------------- */
class BleInputStatus_t : public BLECharacteristicCallbacks
{
private:
    struct Data_t
    {
        BLECharacteristic* pCharacteristic = nullptr;
    };
    Data_t _data;

public:
    BleInputStatus_t(BLEService* pService, const char* uuid)
    {
        _data.pCharacteristic =
            pService->createCharacteristic(uuid, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
        _data.pCharacteristic->setCallbacks(this);
        _data.pCharacteristic->addDescriptor(new BLE2902());
    }

    void updateInput(const BLE_KB::InputFrame_t& newInput)
    {
        uint8_t value[10] = {0};
        value[0] = newInput.btnA;
        value[1] = newInput.btnB;
        value[2] = newInput.btnC;
        value[3] = newInput.btnD;
        value[4] = newInput.valueDialA;
        value[5] = newInput.valueDialB;

        // int16 by le
        value[6] = newInput.countDialA & 0xFF;
        value[7] = (newInput.countDialA >> 8) & 0xFF;
        value[8] = newInput.countDialB & 0xFF;
        value[9] = (newInput.countDialB >> 8) & 0xFF;

        // Update
        _data.pCharacteristic->setValue(value, 10);
        _data.pCharacteristic->notify();
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

        HAL::SaveSystemConfig();
    }

    void onRead(BLECharacteristic* pCharacteristic) override
    {
        auto json = HAL::GetSystemConfigJson();
        pCharacteristic->setValue(json.c_str());
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
        BleSystemConfig_t* syscfg = nullptr;
        bool is_connected = false;
    };
    Data_t _data;

public:
    MyBleShit() {}
    ~MyBleShit()
    {
        delete _data.input;
        delete _data.syscfg;
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
        _data.syscfg = new BleSystemConfig_t(pService, "2335");
        // TODO
        // time
        // msg
        // imu
        pService->start();

        // Advertising
        auto advertising = pServer->getAdvertising();
        advertising->setAppearance(0x00C0);
        advertising->addServiceUUID(pService->getUUID());
        advertising->setScanResponse(false);
        advertising->start();
    }

    void onConnect(BLEServer* pServer) override { _data.is_connected = true; }
    void onDisconnect(BLEServer* pServer) override { _data.is_connected = false; }
    inline bool isConnected() { return _data.is_connected; }

    void updateInput(const BLE_KB::InputFrame_t& newInput) { _data.input->updateInput(newInput); }
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
