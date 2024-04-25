/**
 * @file assets.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "assets.h"
#include "localization/types.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <cstring>
#include <iterator>
#include <string>
#ifndef ESP_PLATFORM
#include "fonts/fonts.h"
#include "images/images.h"
#include <iostream>
#include <fstream>
#endif

AssetPool* AssetPool::_asset_pool = nullptr;

AssetPool* AssetPool::Get()
{
    if (_asset_pool == nullptr)
        _asset_pool = new AssetPool;
    return _asset_pool;
}

StaticAsset_t* AssetPool::getStaticAsset()
{
    if (_data.static_asset == nullptr)
    {
        spdlog::error("static asset not exsit");
        return nullptr;
    }
    return _data.static_asset;
}

bool AssetPool::injectStaticAsset(StaticAsset_t* asset)
{
    if (_data.static_asset != nullptr)
    {
        spdlog::error("static asset already exist");
        return false;
    }

    if (asset == nullptr)
    {
        spdlog::error("invalid static asset ptr");
        return false;
    }

    _data.static_asset = asset;

    // Default local text map
    setLocalTextTo(_data.locale_code);

    spdlog::info("static asset injected");
    return true;
}

void AssetPool::setLocalTextTo(LocaleCode_t code)
{
    if (code == locale_code_en)
        getStaticAsset()->Text.TextEN.getMap(_data.local_text_pool_map);
    else if (code == locale_code_cn)
        getStaticAsset()->Text.TextCN.getMap(_data.local_text_pool_map);
    else if (code == locale_code_jp)
        getStaticAsset()->Text.TextJP.getMap(_data.local_text_pool_map);
}

void AssetPool::setLocaleCode(LocaleCode_t code)
{
    _data.locale_code = code;
    setLocalTextTo(_data.locale_code);
}

void AssetPool::loadFont14(LGFX_SpriteFx* lgfxDevice)
{
    /* ------------------- Load your font by locale code here ------------------- */

    // lgfxDevice->setTextSize(1);
    // if (_data.locale_code == locale_code_en)
    //     lgfxDevice->loadFont(getStaticAsset()->Font.montserrat_semibold_14);
    // else
    //     ...
}

void AssetPool::loadFont16(LGFX_SpriteFx* lgfxDevice) {}

void AssetPool::loadFont24(LGFX_SpriteFx* lgfxDevice) {}

void AssetPool::loadFont72(LGFX_SpriteFx* lgfxDevice) {}

/* -------------------------------------------------------------------------- */
/*                            Static asset generate                           */
/* -------------------------------------------------------------------------- */
StaticAsset_t* AssetPool::CreateStaticAsset()
{
    auto asset_pool = new StaticAsset_t;

    // Copy data
    /* -------------------------------------------------------------------------- */
    /*                                    Fonts                                   */
    /* -------------------------------------------------------------------------- */

    // Copy your font here (or set pointer)
    // std::memcpy(asset_pool->Font.montserrat_semibolditalic_24, montserrat_semibolditalic_24,
    // montserrat_semibolditalic_24_size);

    /* -------------------------------------------------------------------------- */
    /*                                   Images                                   */
    /* -------------------------------------------------------------------------- */

    // Copy your image here (or set pointer)
    // std::memcpy(asset_pool->Image.AppLauncher.icon, image_data_icon, image_data_icon_size);

    return asset_pool;
}

#ifndef ESP_PLATFORM
void AssetPool::CreateStaticAssetBin(StaticAsset_t* assetPool)
{
    /* -------------------------------------------------------------------------- */
    /*                                Output to bin                               */
    /* -------------------------------------------------------------------------- */
    std::string bin_path = "AssetPool.bin";

    std::ofstream outFile(bin_path, std::ios::binary);
    if (!outFile)
        spdlog::error("open {} failed", bin_path);

    outFile.write(reinterpret_cast<const char*>(assetPool), sizeof(StaticAsset_t));
    outFile.close();
    spdlog::info("output asset pool to: {}", bin_path);
}

StaticAsset_t* AssetPool::GetStaticAssetFromBin()
{
    auto asset_pool = new StaticAsset_t;

    // Read from bin
    std::string bin_path = "AssetPool-VAMeter.bin";

    std::ifstream inFile(bin_path, std::ios::binary);
    if (!inFile)
        spdlog::error("open {} failed", bin_path);

    inFile.read(reinterpret_cast<char*>(asset_pool), sizeof(StaticAsset_t));
    inFile.close();

    // // Test
    // for (int i = 0; i < 10; i++)
    // {
    //     spdlog::info(
    //         "0x{:X} 0x{:X}", asset_pool->Font.montserrat_semibold_14[i], asset_pool->Font.montserrat_semibolditalic_72[i]);
    // }

    spdlog::info("load asset pool from: {}", bin_path);
    return asset_pool;
}
#endif
