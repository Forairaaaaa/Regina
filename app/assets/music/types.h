/**
 * @file types.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>

struct Music_t
{
    // https://adamonsoon.github.io/rtttl-play/
    // https://picaxe.com/rtttl-ringtones-for-tune-command/
    struct Rtttl_t
    {
        char NokiaTun[63] = "NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a";

        char SuperMar[228] = "SuperMar:d=4,o=5,b=125:a,8f.,16c,16d,16f,16p,f,16d,16c,16p,16f,16p,16f,16p,8c6,8a.,g,16c,a,8f.,"
                             "16c,16d,16f,16p,f,16d,16c,16p,16f,16p,16a#,16a,16g,2f,16p,8a.,8f.,8c,8a.,f,16g#,16f,16c,16p,8g#.,"
                             "2g,8a.,8f.,8c,8a.,f,16g#,16f,8c,2c6";

        char SuperMarWorld[205] =
            "SuperMar:d=4,o=5,b=125:32p,8g,16c,8e,8g.,16c,8e,16g,16c,16e,16g,8b,a,8p,16c,8g,16c,8e,8g.,16c,8e,16g,16c#,16e,16g,"
            "8b,a,8p,16b,8c6,16b,8c6,8a.,16c6,8b,16a,8g,16f#,8g,8e.,16c,8d,16e,8f,16e,8f,8b.4,16e,8d.,c";
    };
    Rtttl_t Rtttl;
};
