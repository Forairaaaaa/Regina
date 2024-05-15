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
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <BLECharacteristic.h>
#include "../utils/ble_keyboard/BleKeyboard.h"
#include <ArduinoJson.h>

/* -------------------------------------------------------------------------- */
/*                            Device state controll                           */
/* -------------------------------------------------------------------------- */
class BleDeviceState_t : public BLECharacteristicCallbacks
{
public:
    struct State_t
    {
        bool hidKbEnable = true;
    };

private:
    struct Data_t
    {
        BLECharacteristic* pCharacteristic = nullptr;
    };
    Data_t _data;
    State_t _state;

public:
    BleDeviceState_t(BLEService* pService, const char* uuid)
    {
        _data.pCharacteristic =
            pService->createCharacteristic(uuid, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
        _data.pCharacteristic->setCallbacks(this);
    }

    void onWrite(BLECharacteristic* pCharacteristic) override
    {
        std::string value = pCharacteristic->getValue().c_str();
        spdlog::info("state ctrl get:\n {}", value);

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, value);
        if (error != DeserializationError::Ok)
        {
            spdlog::error("parse failed!");
            return;
        }

        // Update state
        _state.hidKbEnable = doc["hidKbEnable"];
    }

    const State_t& getState() { return _state; }
};

/* -------------------------------------------------------------------------- */
/*                                 Input value                                */
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
        uint8_t value[6] = {0};
        value[0] = newInput.btnA;
        value[1] = newInput.btnB;
        value[2] = newInput.btnC;
        value[3] = newInput.btnD;
        value[4] = newInput.valueDialA;
        value[5] = newInput.valueDialB;

        // Update
        _data.pCharacteristic->setValue(value, 6);
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

        HAL::GetSystemConfig().mute = doc["mute"];
        HAL::GetSystemConfig().dialAPinSwaped = doc["dialAPinSwaped"];
        HAL::GetSystemConfig().dialBPinSwaped = doc["dialBPinSwaped"];
        HAL::GetSystemConfig().autoSleepTimeout = doc["autoSleepTimeout"];
        HAL::GetSystemConfig().wifiSsid = doc["wifiSsid"].as<std::string>();
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
/*                      Add my shit base on hid keyboard                      */
/* -------------------------------------------------------------------------- */
class MyBleShit : public BleKeyboard
{
private:
    struct Data_t
    {
        BleDeviceState_t* state = nullptr;
        BleInputStatus_t* input = nullptr;
        BleSystemConfig_t* syscfg = nullptr;
    };
    Data_t _data;

    void onCustom(BLEServer* pServer) override
    {
        spdlog::info("add my custom shit");

        BLEService* pService = pServer->createService("2333");
        _data.state = new BleDeviceState_t(pService, "2334");
        _data.input = new BleInputStatus_t(pService, "2335");
        _data.syscfg = new BleSystemConfig_t(pService, "2336");

        pService->start();
    }

public:
    MyBleShit(const char* deviceName) : BleKeyboard(deviceName) {}
    ~MyBleShit()
    {
        delete _data.state;
        delete _data.input;
        delete _data.syscfg;
    }

    const BleDeviceState_t::State_t& getState() { return _data.state->getState(); }

    void updateInput(const BLE_KB::InputFrame_t& newInput) { _data.input->updateInput(newInput); }
};

static MyBleShit* _my_ble_shit = nullptr;

void HAL_Regina::_ble_init()
{
    spdlog::info("ble init");

    assert(_my_ble_shit == nullptr);
    _my_ble_shit = new MyBleShit("Reginaaaa:)");
    _my_ble_shit->begin();
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

size_t HAL_Regina::bleKeyBoardWrite(const uint8_t c)
{
    if (_my_ble_shit == nullptr)
        return 0;
    if (_my_ble_shit->isConnected() && _my_ble_shit->getState().hidKbEnable)
        return _my_ble_shit->write(c);
    return 0;
}

size_t HAL_Regina::bleKeyBoardWrite(const BLE_KB::MediaKeyReport c)
{
    if (_my_ble_shit == nullptr)
        return 0;
    if (_my_ble_shit->isConnected() && _my_ble_shit->getState().hidKbEnable)
        return _my_ble_shit->write(c);
    return 0;
}
