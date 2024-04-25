/**
 * @file hal_regina.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2024-04-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <hal/hal.h>

class HAL_Regina : public HAL
{
private:
public:
    std::string type() override { return "Regina"; }
};
