/**
 * @file app_launcher.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_launcher.h"
#include "../../hal/hal.h"
#include "../../assets/assets.h"
#include "../utils/system/system.h"
#include "lgfx/v1/lgfx_fonts.hpp"
#include "lgfx/v1/misc/enum.hpp"
#include "spdlog/spdlog.h"
#include <cstddef>
#include <cstdint>
#include <cstdio>

using namespace MOONCAKE::APPS;
using namespace SYSTEM::INPUTS;

// App name
const char* AppLauncher_Packer::getAppName() { return "AppLauncher"; }

// Icon
void* AppLauncher_Packer::getAppIcon() { return nullptr; }

void AppLauncher::onCreate()
{
    setAllowBgRunning(true);
    startApp();
}

// Like setup()...
void AppLauncher::onResume()
{
    spdlog::info("{} onResume", getAppName());
    HAL::GetCanvas()->setTextScroll(true);
    HAL::GetCanvas()->setTextColor(TFT_WHITE, TFT_BLACK);

    // // HAL::GetCanvas()->fillSmoothRoundRect(30, 20, 70, 40, 10, TFT_WHITE);
    // HAL::GetCanvas()->fillRoundRect(30, 20, 70, 40, 10, TFT_WHITE);
    // HAL::CanvasUpdate();

    HAL::GetCanvas()->setTextColor(TFT_WHITE);
    AssetPool::LoadFont12(HAL::GetCanvas());

    // HAL::GetCanvas()->drawStringFix("下，年轻。？()_（）-+=@#￥", 0, 0);
    // HAL::GetCanvas()->drawStringFix("（）-+=@#￥", 0, 12);
    // HAL::CanvasUpdate();
    // HAL::Delay(3000);
}

static std::string _test_text = R"(
ass👴👴12347|||5——+()*&……%￥#@!<>?,./]\[;:'"]👴
，。？~！$$$$$
努力培育良好的年轻人玩原神心态
当下,年轻人玩原神已进入发展快车道,带来了地位的方便。
但是,当我们站在新的历史发展关口,发现年轻人玩原神问题已经严重干扰了问题建设。
这些问题如果得不到有效解决,将会导致了解根本,确保方式进而影响全面分析。
我们不仅要优化沟通,拓宽环节,更要提高方案,倾斜网络。
总而言之要求真务实,抓好年轻人玩原神调研工作,提高质量,做好年轻人玩原神信息工作,
紧跟进度,抓好年轻人玩原神督查工作,高效规范,抓好年轻人玩原神文秘工作,高度负责,
做好年轻人玩原神保密工作,协调推进,做好年轻人玩原神档案工作,积极稳妥,做好年轻人玩原神信访工作,
严格要求,做好年轻人玩原神服务工作。
综观年轻人玩原神发展史,各国都在不断改进巩固方案,推动网络,在重点上,力求完善。以任务为例,
为了年轻人玩原神,巴拿马政府采取了立足当前的政策,使得。鲜明的案例告诉我们,要实现年轻人玩原神的目的,
必须在继承借鉴中发展体系,求真务实,抓好年轻人玩原神调研工作,提高质量,做好年轻人玩原神信息工作,
紧跟进度,抓好年轻人玩原神督查工作,高效规范,抓好年轻人玩原神文秘工作,高度负责,做好年轻人玩原神保密工作,
协调推进,做好年轻人玩原神档案工作,积极稳妥,做好年轻人玩原神信访工作,严格要求,做好年轻人玩原神服务工作。
当前社会现实中的年轻人玩原神现象,既有体制机制的原因,也与意见有直接关系。因此,解决年轻人玩原神问题,
既需要协调内涵,推动精神,发扬热点,制定最大限度,也需要发现出发点,夯实思想,更需要支持地位,统领秩序,
吸引制度保障,促进功夫。只有这样,才能实现年轻人玩原神目标。
)";

// Like loop()...
void AppLauncher::onRunning()
{
    static size_t index = 0;
    index++;
    if (index >= _test_text.size())
        index = 0;
    HAL::GetCanvas()->printf("%c", _test_text[index]);

    // static uint32_t time_count = 0;
    // static int fps = 0;
    // static char string_buffer[10] = {0};
    // fps = 1000 / (HAL::Millis() - time_count);
    // time_count = HAL::Millis();
    // // std::snprintf(string_buffer, 10, "%d", fps);
    // // HAL::GetCanvas()->fillRect(0, 0, 25, 12, TFT_BLACK);
    // // HAL::GetCanvas()->drawString(string_buffer, 0, 0);
    // printf("%d\n", fps);

    HAL::CanvasUpdate();
    // HAL::Delay(10);

    Button::Update();
    if (Button::D()->wasClicked())
        HAL::Reboot();
}

void AppLauncher::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());

    // Release resources here..
    // delete 114514;
}
