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
#include "../utils/ble_keyboard/BleKeyboard.h"

void HAL_Regina::_ble_init()
{
    spdlog::info("ble init");

    _ble_kb_init();
}

/* -------------------------------------------------------------------------- */
/*                             Simple BLE keyboard                            */
/* -------------------------------------------------------------------------- */
static BleKeyboard* _ble_keyboard = nullptr;

void HAL_Regina::_ble_kb_init()
{
    assert(_ble_keyboard == nullptr);
    _ble_keyboard = new BleKeyboard("Reginaaaa:)");
    _ble_keyboard->begin();
}

size_t HAL_Regina::bleKeyBoardWrite(const uint8_t c)
{
    if (_ble_keyboard == nullptr)
        return 0;
    if (_ble_keyboard->isConnected())
        return _ble_keyboard->write(c);
    return 0;
}

size_t HAL_Regina::bleKeyBoardWrite(const BLE_KB::MediaKeyReport c)
{
    if (_ble_keyboard == nullptr)
        return 0;
    if (_ble_keyboard->isConnected())
        return _ble_keyboard->write(c);
    return 0;
}

bool HAL_Regina::isBleConnected()
{
    if (_ble_keyboard != nullptr)
        return _ble_keyboard->isConnected();
    return false;
}
