/**
 * @file wear_levelling.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <stdint.h>
// https://github.com/espressif/esp-idf/blob/v5.1.3/examples/storage/wear_levelling/main/wear_levelling_example_main.c

uint8_t fs_init(void);
uint8_t fs_deinit(void);
uint8_t fs_format(void);
const char* fs_get_base_path();
void* fs_get_wl_handler();
