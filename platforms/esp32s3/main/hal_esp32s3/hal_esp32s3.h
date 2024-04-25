/**
 * @file hal_esp32s3.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2024-04-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <hal/hal.h>

class HAL_ESP32S3 : public HAL
{
private:
public:
    std::string type() override { return "ESP32S3"; }
};
