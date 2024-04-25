/**
 * @file assets.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>
#include "fonts/types.h"
#include "images/types.h"
#include "theme/types.h"
#include "localization/types.h"
#include "../hal/types.h"
#include "../hal/hal.h"

/**
 * @brief A struct to define static binary asset
 *
 */
struct StaticAsset_t
{
    FontPool_t Font;
    ImagePool_t Image;
    ColorPool_t Color;
    TextPool_t Text;
};

/**
 * @brief A Class to handle static asset
 *
 */
class AssetPool
{
    /* -------------------------------------------------------------------------- */
    /*                                  Singleton                                 */
    /* -------------------------------------------------------------------------- */
private:
    static AssetPool* _asset_pool;

public:
    static AssetPool* Get();

private:
    struct Data_t
    {
        StaticAsset_t* static_asset = nullptr;
        LocalTextPoolMap_t local_text_pool_map;
        LocaleCode_t locale_code = locale_code_en;
    };
    Data_t _data;

    /* ------------------------------ Static asset ------------------------------ */
public:
    StaticAsset_t* getStaticAsset();
    bool injectStaticAsset(StaticAsset_t* pool);

    /* ---------------------------------- Text ---------------------------------- */
public:
    void setLocalTextTo(LocaleCode_t code);
    void setLocaleCode(LocaleCode_t code);
    LocaleCode_t getLocaleCode() { return _data.locale_code; }
    bool isLocaleEn() { return _data.locale_code == locale_code_en; }
    inline const LocalTextPoolMap_t& getText() { return _data.local_text_pool_map; }

    /* ---------------------------------- Font ---------------------------------- */
public:
    void loadFont14(LGFX_SpriteFx* lgfxDevice);
    void loadFont16(LGFX_SpriteFx* lgfxDevice);
    void loadFont24(LGFX_SpriteFx* lgfxDevice);
    void loadFont72(LGFX_SpriteFx* lgfxDevice);

    /* ------------------------------- Static wrap ------------------------------ */
public:
    static StaticAsset_t* GetStaticAsset() { return Get()->getStaticAsset(); }
    static bool InjectStaticAsset(StaticAsset_t* asset) { return Get()->injectStaticAsset(asset); }

    static const ImagePool_t& GetImage() { return GetStaticAsset()->Image; }
    static const ColorPool_t& GetColor() { return GetStaticAsset()->Color; }
    static const TextPool_t& GetTextPool() { return GetStaticAsset()->Text; }
    static const LocalTextPoolMap_t& GetText() { return Get()->getText(); }

    static void SetLocaleCode(LocaleCode_t code) { Get()->setLocaleCode(code); }
    static void SetLocalTextTo(LocaleCode_t code) { Get()->setLocalTextTo(code); }
    static LocaleCode_t GetLocaleCode() { return Get()->getLocaleCode(); }
    static bool IsLocaleEn() { return Get()->isLocaleEn(); }

    static void LoadFont14(LGFX_SpriteFx* lgfxDevice) { Get()->loadFont14(lgfxDevice); }
    static void LoadFont16(LGFX_SpriteFx* lgfxDevice) { Get()->loadFont16(lgfxDevice); }
    static void LoadFont24(LGFX_SpriteFx* lgfxDevice) { Get()->loadFont24(lgfxDevice); }
    static void LoadFont72(LGFX_SpriteFx* lgfxDevice) { Get()->loadFont72(lgfxDevice); }

public:
    /* -------------------------- Generate static asset ------------------------- */
    static StaticAsset_t* CreateStaticAsset();
#ifndef ESP_PLATFORM
    static void CreateStaticAssetBin(StaticAsset_t* assetPool);
    static StaticAsset_t* GetStaticAssetFromBin();
#endif
};
