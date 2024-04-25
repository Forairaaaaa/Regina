#pragma once
#include "text_pool_map.h"

struct TextPool_en_t
{
    char AppName_Settings[9] = "Settings";

    void getMap(LocalTextPoolMap_t& map)
    {
        map.AppName_Settings = AppName_Settings;
    }
};
