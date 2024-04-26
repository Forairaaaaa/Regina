/**
 * @file hal_config.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

/**
 * @brief Pin configs
 *
 */
// LCD
#define HAL_PIN_OLED_CS 9
#define HAL_PIN_OLED_DC 18
#define HAL_PIN_OLED_RST 19
#define HAL_PIN_OLED_SDA 20
#define HAL_PIN_OLED_SCL 21

// Button
#define HAL_PIN_BTN_A 16
#define HAL_PIN_BTN_B 3
#define HAL_PIN_BTN_C 2
#define HAL_PIN_BTN_D 8

// Dial
#define HAL_PIN_DIAL_CE 0
#define HAL_PIN_DIAL_PL 6
#define HAL_PIN_DIAL_CLK 7
#define HAL_PIN_DIAL_DATA 1

// I2C
#define HAL_PIN_I2C_SCL 10
#define HAL_PIN_I2C_SDA 11

// Buzzer
#define HAL_PIN_BUZZ 22

// Mic
#define HAL_PIN_MIC 4

// IMU
#define HAL_PIN_IMU_INT1 23
#define HAL_PIN_IMU_INT2 17

// RTC
#define HAL_PIN_RTC_INT 15

// PMU
#define HAL_PIN_PMU_INT 5

// HAL internal display logger
#define HAL_LOGGER_INIT()                                                                                                      \
    _canvas->setFont(&fonts::Font0);                                                                                           \
    _canvas->setTextSize(1);                                                                                                   \
    _canvas->setTextScroll(true);                                                                                              \
    _canvas->setCursor(0, 0)

#define HAL_LOG(fmt, args...)                                                                                                  \
    _canvas->setTextColor(TFT_LIGHTGRAY, TFT_BLACK);                                                                           \
    _canvas->printf(fmt, ##args);                                                                                              \
    _canvas->print('\n');                                                                                                      \
    _canvas->pushSprite(0, 0)

#define HAL_LOG_TAG_START()                                                                                                    \
    _canvas->setTextColor(TFT_LIGHTGRAY, TFT_BLACK);                                                                           \
    _canvas->print(" [")

#define HAL_LOG_TAG_END()                                                                                                      \
    _canvas->setTextColor(TFT_LIGHTGRAY, TFT_BLACK);                                                                           \
    _canvas->print("] ")

#define HAL_LOG_INFO(fmt, args...)                                                                                             \
    HAL_LOG_TAG_START();                                                                                                       \
    _canvas->setTextColor(TFT_GREENYELLOW, TFT_BLACK);                                                                         \
    _canvas->print("info");                                                                                                    \
    HAL_LOG_TAG_END();                                                                                                         \
    HAL_LOG(fmt, ##args)

#define HAL_LOG_WARN(fmt, args...)                                                                                             \
    HAL_LOG_TAG_START();                                                                                                       \
    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);                                                                              \
    _canvas->print("warn");                                                                                                    \
    HAL_LOG_TAG_END();                                                                                                         \
    HAL_LOG(fmt, ##args)

#define HAL_LOG_ERROR(fmt, args...)                                                                                            \
    HAL_LOG_TAG_START();                                                                                                       \
    _canvas->setTextColor(TFT_RED, TFT_BLACK);                                                                                 \
    _canvas->print("error");                                                                                                   \
    HAL_LOG_TAG_END();                                                                                                         \
    HAL_LOG(fmt, ##args)
