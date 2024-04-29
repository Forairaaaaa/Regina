/**
 * @file app_startup_anim.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_startup_anim.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../utils/system/system.h"
#include "core/easing_path/easing_path.h"
#include "lgfx/v1/misc/enum.hpp"
#include "spdlog/spdlog.h"
#include <smooth_ui_toolkit.h>

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;
using namespace SmoothUIToolKit;

// App name
const char* AppStartupAnim_Packer::getAppName() { return "AppStartupAnim"; }

// Like setup()...
void AppStartupAnim::onResume()
{
    spdlog::info("{} onResume", getAppName());

    AssetPool::LoadFont12(HAL::GetCanvas());
    HAL::GetCanvas()->setTextSize(2);
    HAL::GetCanvas()->setTextColor(TFT_BLACK, TFT_WHITE);
    HAL::GetCanvas()->setTextDatum(middle_left);

    Transition4D transition;
    transition.setDuration(400);
    transition.setTransitionPath(EasingPath::easeOutBack);
    transition.jumpTo(17, -30, 95, 30);
    transition.moveTo(17, 17, 95, 30);
    while (!transition.isFinish())
    {
        transition.update(HAL::Millis());
        auto frame = transition.getValue();

        HAL::GetCanvas()->fillScreen(TFT_BLACK);
        HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, 8, TFT_WHITE);
        HAL::GetCanvas()->drawString("Regina", frame.x + 10, frame.y + 15);
        HAL::CanvasUpdate();
        HAL::FeedTheDog();
    }

    HAL::Delay(600);

    transition.setDuration(500);
    transition.moveTo(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height());
    while (!transition.isFinish())
    {
        transition.update(HAL::Millis());
        auto frame = transition.getValue();

        HAL::GetCanvas()->fillScreen(TFT_BLACK);
        HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, 8, TFT_WHITE);
        HAL::CanvasUpdate();
        HAL::FeedTheDog();
    }

    HAL::Delay(3000);

    destroyApp();
}

void AppStartupAnim::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }
