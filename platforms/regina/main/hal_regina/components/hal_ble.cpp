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

static BleKeyboard* _ble_keyboard = nullptr;

void HAL_Regina::_ble_init()
{
    spdlog::info("ble init");

    assert(_ble_keyboard == nullptr);
    _ble_keyboard = new BleKeyboard("Regina-Keyboard");
    _ble_keyboard->begin();
}
