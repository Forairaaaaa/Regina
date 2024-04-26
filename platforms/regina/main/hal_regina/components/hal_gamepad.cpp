/**
 * @file hal_gamepad.cpp
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
#include <driver/gpio.h>

void HAL_Regina::_gamepad_init()
{
    spdlog::info("gamepad init");

    std::vector<uint8_t> pin_list = {HAL_PIN_BTN_A, HAL_PIN_BTN_B, HAL_PIN_BTN_C, HAL_PIN_BTN_D};
    for (const auto& i : pin_list)
    {
        gpio_reset_pin((gpio_num_t)i);
        gpio_set_direction((gpio_num_t)i, GPIO_MODE_INPUT);
    }

    // /* -------------------------------------------------------------------------- */
    // /*                                    Test                                    */
    // /* -------------------------------------------------------------------------- */
    // while (1)
    // {
    //     spdlog::info("{} {} {} {}",
    //                  getButton(GAMEPAD::BTN_A),
    //                  getButton(GAMEPAD::BTN_B),
    //                  getButton(GAMEPAD::BTN_C),
    //                  getButton(GAMEPAD::BTN_D));
    //     delay(50);
    // }
}

bool HAL_Regina::getButton(GAMEPAD::GamePadButton_t button)
{
    if (button == GAMEPAD::BTN_A)
        return !(bool)gpio_get_level((gpio_num_t)HAL_PIN_BTN_A);
    if (button == GAMEPAD::BTN_B)
        return !(bool)gpio_get_level((gpio_num_t)HAL_PIN_BTN_B);
    if (button == GAMEPAD::BTN_C)
        return !(bool)gpio_get_level((gpio_num_t)HAL_PIN_BTN_C);
    if (button == GAMEPAD::BTN_D)
        return !(bool)gpio_get_level((gpio_num_t)HAL_PIN_BTN_D);

    return false;
}
