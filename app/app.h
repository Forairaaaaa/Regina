/**
 * @file app.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <mooncake.h>
#include <functional>
#include "assets/assets.h"
#include "hal/hal.h"

namespace APP
{
    struct SetupCallback_t
    {
        std::function<void()> sharedDataInjection = nullptr;
        std::function<void()> AssetPoolInjection = nullptr;
        std::function<void()> HalInjection = nullptr;
    };

    void Setup(SetupCallback_t callback);
    void Loop();
    void Destroy();
} // namespace APP
