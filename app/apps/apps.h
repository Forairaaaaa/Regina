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
#include "app/app.h"
#include "app_template/app_template.h"
#include "app_launcher/app_launcher.h"
#include "app_startup_anim/app_startup_anim.h"
#include "app_desktop/app_desktop.h"
#include "app_sleep_daemon/app_sleep_daemon.h"
#include "app_input_daemon/app_input_daemon.h"
#include "app_settings/app_settings.h"
#include "app_notification/app_notification.h"
#include <vector>
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
 * @brief Install and start default startup app
 *
 * @param mooncake
 */
inline void app_install_default_startup_app(MOONCAKE::Mooncake* mooncake)
{
    std::vector<MOONCAKE::APP_PACKER_BASE*> app_packers;

    app_packers.push_back(new MOONCAKE::APPS::AppDesktop_Packer);
    app_packers.push_back(new MOONCAKE::APPS::AppNotification_Packer);
    app_packers.push_back(new MOONCAKE::APPS::AppInputDaemon_Packer);
    app_packers.push_back(new MOONCAKE::APPS::AppSleepDaemon_Packer);

    for (const auto& i : app_packers)
    {
        mooncake->installApp(i);
        mooncake->createAndStartApp(i);
    }
}

/**
 * @brief Install apps
 *
 * @param mooncake
 */
inline void app_install_apps(MOONCAKE::Mooncake* mooncake)
{
    // mooncake->installApp(new MOONCAKE::APPS::AppTemplate_Packer);
    // mooncake->installApp(new MOONCAKE::APPS::AppSettings_Packer);
    /* Install app locator (Don't remove) */
}
