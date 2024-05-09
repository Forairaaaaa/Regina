/**
 * @file button.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "button.h"
#include "../../../../../hal/hal.h"
#include "hal/types.h"

using namespace SYSTEM::INPUTS;

void Button::update() { m5::Button_Class::setRawState(HAL::Millis(), HAL::GetButton(_button)); }

static Button* _button_a = nullptr;
Button* Button::A()
{
    // Lazy loading
    if (_button_a == nullptr)
        _button_a = new Button(GAMEPAD::BTN_A);
    return _button_a;
}

static Button* _button_b = nullptr;
Button* Button::B()
{
    // Lazy loading
    if (_button_b == nullptr)
        _button_b = new Button(GAMEPAD::BTN_B);
    return _button_b;
}

static Button* _button_c = nullptr;
Button* Button::C()
{
    // Lazy loading
    if (_button_c == nullptr)
        _button_c = new Button(GAMEPAD::BTN_C);
    return _button_c;
}

static Button* _button_d = nullptr;
Button* Button::D()
{
    // Lazy loading
    if (_button_d == nullptr)
        _button_d = new Button(GAMEPAD::BTN_D);
    return _button_d;
}

#ifdef PLATFORM_BUILD_REGINA
static ButtonPwr* _button_pwr = nullptr;
ButtonPwr* Button::Power()
{
    if (_button_pwr == nullptr)
        _button_pwr = new ButtonPwr;
    return _button_pwr;
}

bool ButtonPwr::wasClicked() { return HAL::WasPowerButtonClicked(); }
#else
static Button* _button_power = nullptr;
Button* Button::Power()
{
    // Lazy loading
    if (_button_power == nullptr)
        _button_power = new Button(GAMEPAD::BTN_PWR);
    return _button_power;
}
#endif

void Button::Update()
{
    A()->update();
    B()->update();
    C()->update();
    D()->update();
}
