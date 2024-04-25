#pragma once
#include "text_pool_map.h"

struct TextPool_cn_t
{
    char AppName_Settings[7] = "设置";

    void getMap(LocalTextPoolMap_t& map)
    {
        map.AppName_Settings = AppName_Settings;
    }
};
