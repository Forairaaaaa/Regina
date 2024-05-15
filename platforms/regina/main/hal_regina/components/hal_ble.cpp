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
        BLECharacteristic* state_char = nullptr;
    };
    Data_t _data;
    State_t _state;

public:
    BleDeviceState_t(BLEService* pService, const char* uuid)
    {
        _data.state_char =
            pService->createCharacteristic(uuid, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    }

    void onWrite(BLECharacteristic* pCharacteristic)
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


/* -------------------------------------------------------------------------- */
/*                      Add my shit base on hid keyboard                      */
/* -------------------------------------------------------------------------- */
class MyBleShit : public BleKeyboard
{
private:
    struct Data_t
    {
        BleDeviceState_t* state = nullptr;
    };
    Data_t _data;

    void onCustom(BLEServer* pServer) override
    {
        spdlog::info("add my custom shit");

        BLEService* pService = pServer->createService("2333");
        _data.state = new BleDeviceState_t(pService, "2334");
    }

public:
    MyBleShit(const char* deviceName) : BleKeyboard(deviceName) {}

    const BleDeviceState_t::State_t& getState() { return _data.state->getState(); }
};

static MyBleShit* _ble_device = nullptr;

void HAL_Regina::_ble_init()
{
    spdlog::info("ble init");

    assert(_ble_device == nullptr);
    _ble_device = new MyBleShit("Reginaaaa:)");
    _ble_device->begin();
}

size_t HAL_Regina::bleKeyBoardWrite(const uint8_t c)
{
    if (_ble_device == nullptr)
        return 0;
    if (_ble_device->isConnected() && _ble_device->getState().hidKbEnable)
        return _ble_device->write(c);
    return 0;
}

size_t HAL_Regina::bleKeyBoardWrite(const BLE_KB::MediaKeyReport c)
{
    if (_ble_device == nullptr)
        return 0;
    if (_ble_device->isConnected() && _ble_device->getState().hidKbEnable)
        return _ble_device->write(c);
    return 0;
}

bool HAL_Regina::isBleConnected()
{
    if (_ble_device != nullptr)
        return _ble_device->isConnected();
    return false;
}
