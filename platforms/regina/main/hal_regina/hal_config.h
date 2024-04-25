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
#define HAL_PIN_LCD_MOSI 35
#define HAL_PIN_LCD_MISO -1
#define HAL_PIN_LCD_SCLK 36
#define HAL_PIN_LCD_DC 34
#define HAL_PIN_LCD_CS 37
#define HAL_PIN_LCD_RST 33
#define HAL_PIN_LCD_BUSY -1
#define HAL_PIN_LCD_BL 38

// Button
#define HAL_PIN_SIDE_BTN 0

// Encoder
#define HAL_PIN_ENCODER_A 3
#define HAL_PIN_ENCODER_S 2
#define HAL_PIN_ENCODER_B 1

// I2C
#define HAL_PIN_I2C_SCL 6
#define HAL_PIN_I2C_SDA 5

// Buzzer
#define HAL_PIN_BUZZ 14

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
