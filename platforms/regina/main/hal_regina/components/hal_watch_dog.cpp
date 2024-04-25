/**
 * @file hal_watch_dog.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_regina.h"
#include "../hal_config.h"
#include <esp_system.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_err.h>
#include <esp_task_wdt.h>
#include <mooncake.h>
// Refs:
// https://github.com/espressif/esp-idf/blob/v5.2.1/examples/system/task_watchdog/main/task_watchdog_example_main.c
// https://docs.espressif.com/projects/esp-idf/en/v5.2.1/esp32/api-reference/system/wdts.html

void HAL_Regina::_watch_dog_init()
{
    spdlog::info("watch dog init");

    // // Init twdt
    // esp_task_wdt_config_t twdt_config = {
    //     .timeout_ms = 3000,
    //     .idle_core_mask = (1 << portNUM_PROCESSORS) - 1, // Bitmask of all cores
    //     // .idle_core_mask = 1 << 1, // Only IDLE1
    //     .trigger_panic = true,
    // };
    // ESP_ERROR_CHECK(esp_task_wdt_init(&twdt_config));

    // // Subscribes main task
    // ESP_ERROR_CHECK(esp_task_wdt_add(NULL));
    // ESP_ERROR_CHECK(esp_task_wdt_status(NULL));

    // /* -------------------------------------------------------------------------- */
    // /*                                    Test                                    */
    // /* -------------------------------------------------------------------------- */
    // int b = 2;
    // while (1)
    // {
    //     // delay(5);
    //     int a = b * b;
    //     feedTheDog();
    // }
}

void HAL_Regina::feedTheDog()
{
    // esp_task_wdt_reset();
    // SB idle wdt 😅
    vTaskDelay(1);
}

void HAL_Regina::reboot() { esp_restart(); }
