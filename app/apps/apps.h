/**
 * @file apps.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "app_template/app_template.h"
#include "app_launcher/app_launcher.h"
#include "app_startup_anim/app_startup_anim.h"
#include "app_desktop/app_desktop.h"
/* Header files locator (Don't remove) */

/**
 * @brief Run startup anim app
 *
 * @param mooncake
 */
inline void app_run_startup_anim(MOONCAKE::Mooncake* mooncake)
{
    /* -------------------- Install and run startup anim here ------------------- */
    auto startup_anim = new MOONCAKE::APPS::AppStartupAnim_Packer;

    mooncake->createAndStartApp(startup_anim);
    while (1)
    {
        mooncake->update();
        if (mooncake->getAppManager()->getCreatedAppNum() == 0)
            break;
    }

    delete startup_anim;
}

/**
 * @brief Install default startup app
 *
 * @param mooncake
 */
inline void app_install_default_startup_app(MOONCAKE::Mooncake* mooncake)
{
    // Install and start desktop at startup
    auto desktop = new MOONCAKE::APPS::AppDesktop_Packer;
    mooncake->installApp(desktop);
    mooncake->createAndStartApp(desktop);
}

/**
 * @brief Install apps
 *
 * @param mooncake
 */
inline void app_install_apps(MOONCAKE::Mooncake* mooncake)
{
    // mooncake->installApp(new MOONCAKE::APPS::AppTemplate_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppDesktop_Packer);
    /* Install app locator (Don't remove) */
}
