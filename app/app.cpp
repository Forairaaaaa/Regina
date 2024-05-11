/**
 * @file app.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app.h"
#include "apps/apps.h"
#include "hal/hal.h"
#include "assets/assets.h"
#include "shared/shared.h"
#include "spdlog/spdlog.h"
#include <mooncake.h>

using namespace MOONCAKE;
static Mooncake* _mooncake = nullptr;

void APP::Setup(SetupCallback_t callback)
{
    spdlog::info("app setup");

    /* -------------------------------------------------------------------------- */
    /*                            Asset pool injection                            */
    /* -------------------------------------------------------------------------- */
    spdlog::info("asset pool injection:");
    if (callback.AssetPoolInjection != nullptr)
        callback.AssetPoolInjection();
    else
        spdlog::warn("empty callback");

    /* -------------------------------------------------------------------------- */
    /*                            Shared data injection                           */
    /* -------------------------------------------------------------------------- */
    spdlog::info("shared data injection:");
    if (callback.sharedDataInjection != nullptr)
        callback.sharedDataInjection();
    else
    {
        spdlog::info("empty callback, inject type base");
        SharedData::Inject(new SharedData);
    }

    /* -------------------------------------------------------------------------- */
    /*                                HAL injection                               */
    /* -------------------------------------------------------------------------- */
    spdlog::info("hal injection:");
    if (callback.HalInjection != nullptr)
        callback.HalInjection();
    else
        spdlog::warn("empty callback");

    /* -------------------------------------------------------------------------- */
    /*                                Mooncake apps                               */
    /* -------------------------------------------------------------------------- */
    _mooncake = new Mooncake;
    _mooncake->init();

    app_run_startup_anim(_mooncake);
    app_install_default_startup_app(_mooncake);
    app_install_apps(_mooncake);
}

void APP::Loop()
{
    _mooncake->update();
    HAL::FeedTheDog();
}

void APP::Destroy()
{
    delete _mooncake;
    HAL::Destroy();
    spdlog::warn("app destroy");
}
