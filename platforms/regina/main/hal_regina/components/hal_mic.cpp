// /**
//  * @file hal_mic.cpp
//  * @author Forairaaaaa
//  * @brief
//  * @version 0.1
//  * @date 2024-04-27
//  *
//  * @copyright Copyright (c) 2024
//  *
//  */
// #include <mooncake.h>
// #include "../hal_regina.h"
// #include "../hal_config.h"
// #include <Arduino.h>
// #include <smooth_ui_toolkit.h>

// using namespace SmoothUIToolKit;

// static constexpr size_t _samples_num = 256;
// static constexpr uint32_t _sample_rate = 44100;

// static RingBuffer<int, _samples_num>* _sample_buffer = nullptr;
// static adc_continuos_data_t* _result_buffer = nullptr;
// static volatile int _sample_cycle_count = 0;
// static volatile bool _sample_cycled_flag = false;

// void ARDUINO_ISR_ATTR _adc_complete_isr()
// {
//     if (analogContinuousRead(&_result_buffer, 0))
//     {
//         // Push sample
//         _sample_buffer->put(_result_buffer[0].avg_read_raw);

//         _sample_cycle_count = _sample_cycle_count + 1;
//         if (_sample_cycle_count > _samples_num)
//         {
//             _sample_cycle_count = 0;
//             _sample_cycled_flag = true;
//         }
//     }
// }

// void _mic_adc_init()
// {
//     static uint8_t adc_pins[1] = {HAL_PIN_MIC};

//     _sample_buffer = new RingBuffer<int, _samples_num>;

//     analogContinuousSetWidth(12);
//     // analogContinuousSetAtten(ADC_0db);
//     analogContinuous(adc_pins, 1, 5, _sample_rate, _adc_complete_isr);
//     analogContinuousStart();
// }

// void HAL_Regina::_mic_init()
// {
//     spdlog::info("mic init");

//     // _mic_adc_init();

//     /* -------------------------------------------------------------------------- */
//     /*                                    Test                                    */
//     /* -------------------------------------------------------------------------- */
//     // while (1)
//     // {
//     //     // printf("%d\n", analogRead(HAL_PIN_MIC));
//     //     // delay(20);

//     //     // if (analogContinuousRead(&result, 0))
//     //     // {
//     //     //     analogContinuousStop();
//     //     //     printf("m:%d\n", result[0].avg_read_raw);
//     //     //     analogContinuousStart();
//     //     // }
//     //     // delay(5);

//     //     if (_sample_cycled_flag)
//     //     {
//     //         _sample_cycled_flag = false;
//     //         analogContinuousStop();
//     //         _sample_buffer->peekAll([](const int& sample) { printf("m:%d\n", sample); });
//     //         analogContinuousStart();
//     //     }
//     // }
// }
