/**
 * @file hal_gamepad.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/lovyan03/LovyanGFX/blob/master/examples/HowToUse/2_user_setting/2_user_setting.ino
 * @version 0.1
 * @date 2023-11-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../hal_regina.h"
#include "../hal_config.h"
#include <mooncake.h>

void HAL_Regina::_disp_init()
{
    spdlog::info("display init");

    if (_data.display != nullptr)
    {
        spdlog::info("already inited");
        return;
    }

    // TODO

    // _data.canvas = new LGFX_SpriteFx(_data.display);
    // _data.canvas->createSprite(_data.display->width(), _data.display->height());
}
