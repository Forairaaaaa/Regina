/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <app.h>
#include "hal_desktop/hal_desktop.hpp"

void setup()
{
    APP::SetupCallback_t callback;

    callback.AssetPoolInjection = []() {
        // 自产自销
        auto asset_pool = AssetPool::CreateStaticAsset();
        AssetPool::CreateStaticAssetBin(asset_pool);
        delete asset_pool;
        AssetPool::InjectStaticAsset(AssetPool::GetStaticAssetFromBin());
    };

    callback.HalInjection = []() { HAL::Inject(new HAL_Desktop(128, 64)); };

    APP::Setup(callback);
}

void loop() { APP::Loop(); }
