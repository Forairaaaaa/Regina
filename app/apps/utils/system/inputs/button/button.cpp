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

using namespace SYSTEM::INPUTS;

void Button::update() { m5::Button_Class::setRawState(HAL::Millis(), HAL::GetButton(_button)); }

static Button* _encoder_button = nullptr;
Button* Button::Encoder()
{
    // Lazy loading
    if (_encoder_button == nullptr)
        _encoder_button = new Button(GAMEPAD::BTN_A);
    return _encoder_button;
}

static Button* _side_button = nullptr;
Button* Button::Side()
{
    // Lazy loading
    if (_side_button == nullptr)
        _side_button = new Button(GAMEPAD::BTN_B);
    return _side_button;
}

void Button::Update()
{
    Encoder()->update();
    Side()->update();
}
