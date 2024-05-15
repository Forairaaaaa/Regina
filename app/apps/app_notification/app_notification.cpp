/**
 * @file app_notification.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_notification.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../utils/system/system.h"
#include "lgfx/v1/misc/enum.hpp"

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppNotification_Packer::getAppName() { return "Notification"; }

// Like setup()...
void AppNotification::onResume() { spdlog::info("{} onResume", getAppName()); }

void AppNotification::onRunning() {}

void AppNotification::onDestroy() { spdlog::info("{} onDestroy", getAppName()); }
