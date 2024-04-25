// /**
//  * @file hal_i2c.cpp
//  * @author Forairaaaaa
//  * @brief
//  * @version 0.1
//  * @date 2023-12-15
//  *
//  * @copyright Copyright (c) 2023
//  *
//  */
// #include "../hal_regina.h"
// #include "../hal_config.h"
// #include <mooncake.h>
// #include <driver/i2c.h>

// void HAL_Regina::_i2c_init()
// {
//     // delay(3000);
//     spdlog::info("i2c bus init");

//     // Init
//     i2c_config_t conf;
//     conf.mode = I2C_MODE_MASTER;
//     conf.sda_io_num = HAL_PIN_I2C_SDA;
//     conf.scl_io_num = HAL_PIN_I2C_SCL;
//     conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
//     conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
//     conf.master.clk_speed = 400000;
//     conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

//     i2c_param_config(I2C_NUM_0, &conf);
//     if (i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0) != ESP_OK)
//     {
//         popFatalError("I2C init failed");
//     }

//     // Scan
//     uint8_t device_num = 0;
//     uint8_t WRITE_BIT = I2C_MASTER_WRITE;
//     uint8_t ACK_CHECK_EN = 0x1;
//     uint8_t address;
//     for (int i = 0; i < 128; i += 16)
//     {
//         for (int j = 0; j < 16; j++)
//         {
//             fflush(stdout);
//             address = i + j;
//             i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//             i2c_master_start(cmd);
//             i2c_master_write_byte(cmd, (address << 1) | WRITE_BIT, ACK_CHECK_EN);
//             i2c_master_stop(cmd);
//             esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, portMAX_DELAY);
//             i2c_cmd_link_delete(cmd);
//             if (ret == ESP_OK)
//             {
//                 if (address == 0)
//                     continue;
//                 spdlog::info("found at {:#x}", address);
//                 device_num++;
//             }
//         }
//     }
//     spdlog::info("found {} device", device_num);

//     if (device_num < 2)
//         popWarning("Error I2C\nDevice Num");
// }
