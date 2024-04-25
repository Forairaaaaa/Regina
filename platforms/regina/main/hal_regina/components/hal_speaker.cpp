// /**
//  * @file hal_speaker.cpp
//  * @author Forairaaaaa
//  * @brief
//  * @version 0.1
//  * @date 2023-11-08
//  *
//  * @copyright Copyright (c) 2023
//  *
//  */
// #include "../hal_regina.h"
// #include "../hal_config.h"
// #include <mooncake.h>
// #include <Arduino.h>

// #define NOTE_C4 262
// #define NOTE_CS4 277
// #define NOTE_D4 294
// #define NOTE_DS4 311
// #define NOTE_E4 330
// #define NOTE_F4 349
// #define NOTE_FS4 370
// #define NOTE_G4 392
// #define NOTE_GS4 415
// #define NOTE_A4 440
// #define NOTE_AS4 466
// #define NOTE_B4 494

// void HAL_Regina::_seaker_init()
// {
//     initArduino();

//     // <BUG> tone affect brightness, seems like resolution changed
//     // Kind of fix, call tone after display init, it only affect once
//     beep(100, 5);
// }

// void HAL_Regina::beep(float frequency, uint32_t duration)
// {
//     if (_config.beepOn)
//         tone(HAL_PIN_BUZZ, frequency, duration);
// }

// void HAL_Regina::beepStop()
// {
//     if (_config.beepOn)
//         noTone(HAL_PIN_BUZZ);
// }
