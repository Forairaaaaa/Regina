/**
 * @file app_main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <app.h>
#include "hal_esp32s3/hal_esp32s3.h"
#include <esp_partition.h>
#include <spi_flash_mmap.h>
#include <nvs_flash.h>

extern "C" void app_main(void)
{
    spdlog::set_pattern("[%H:%M:%S] [%L] %v");

    APP::SetupCallback_t callback;

    callback.AssetPoolInjection = []() {
        // Simple reference
        AssetPool::InjectStaticAsset(AssetPool::CreateStaticAsset());

        // // Or load from flash
        // // Get asser pool from flash
        // char* static_asset;
        // const esp_partition_t* part;
        // spi_flash_mmap_handle_t handler;
        // esp_err_t err;
        // nvs_flash_init();
        // part = esp_partition_find_first((esp_partition_type_t)233, (esp_partition_subtype_t)0x23, NULL);
        // if (part == 0)
        // {
        //     spdlog::error("asset pool partition not found!\n");
        //     return;
        // }
        // err = esp_partition_mmap(part, 0, 2 * 1024 * 1024, ESP_PARTITION_MMAP_DATA, (const void**)&static_asset, &handler);
        // if (err != ESP_OK)
        // {
        //     spdlog::error("map asset pool failed!\n");
        //     return;
        // }
        // spdlog::info("asset pool maped at: {}", (void*)static_asset);

        // // Inject
        // AssetPool::InjectStaticAsset((StaticAsset_t*)static_asset);
    };

    callback.HalInjection = []() { HAL::Inject(new HAL_ESP32S3); };

    APP::Setup(callback);

    while (1)
    {
        APP::Loop();
    }
}
