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

    Transition4D transition;
    // HELL:

    /* ---------------------------------- Image --------------------------------- */
    transition.jumpTo(0, HAL::GetCanvas()->height(), 0, 0);
    transition.moveTo(0, -39, 0, 0);

    transition.setDuration(700);
    transition.setTransitionPath(EasingPath::easeOutQuad);

    while (!transition.isFinish())
    {
        transition.update(HAL::Millis());
        auto frame = transition.getValue();

        HAL::GetCanvas()->fillScreen(TFT_BLACK);
        HAL::GetCanvas()->pushImage(0,
                                    frame.y,
                                    AssetPool::GetImage().StartupAnim.warma_halftone_width,
                                    AssetPool::GetImage().StartupAnim.warma_halftone_height,
                                    AssetPool::GetImage().StartupAnim.warma_halftone);
        HAL::CanvasUpdate();
        HAL::FeedTheDog();
    }

    HAL::Delay(1000);

    /* ---------------------------------- Panel --------------------------------- */
    transition.jumpTo((HAL::GetCanvas()->width() - 24) / 2, HAL::GetCanvas()->height(), 24, 12);
    transition.moveTo(0, 0, HAL::GetCanvas()->width(), HAL::GetCanvas()->height());

    transition.setDuration(700);
    transition.setTransitionPath(EasingPath::easeOutBack);

    transition.getYTransition().setDuration(500);
    transition.getXTransition().setDelay(70);
    transition.getWTransition().setDelay(70);
    transition.getHTransition().setDelay(70);

    while (!transition.isFinish())
    {
        transition.update(HAL::Millis());
        auto frame = transition.getValue();

        HAL::GetCanvas()->fillScreen(TFT_BLACK);

        HAL::GetCanvas()->pushImage(0,
                                    frame.y - 103,
                                    AssetPool::GetImage().StartupAnim.warma_halftone_width,
                                    AssetPool::GetImage().StartupAnim.warma_halftone_height,
                                    AssetPool::GetImage().StartupAnim.warma_halftone);
        HAL::GetCanvas()->fillRect(frame.x, frame.y, frame.w, frame.h, TFT_BLACK);
        HAL::GetCanvas()->fillRoundRect(frame.x, frame.y, frame.w, frame.h, 8, TFT_WHITE);

        HAL::CanvasUpdate();
        HAL::FeedTheDog();
    }

    // HAL::GetCanvas()->pushImage(0, 0, 128, 128, AssetPool::GetImage().StartupAnim.warma_halftone);
    // HAL::CanvasUpdate();

    // HAL::Delay(1000);
    // goto HELL;

    destroyApp();
}

void AppStartupAnim::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }
