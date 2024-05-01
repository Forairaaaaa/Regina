/**
 * @file types.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>

/* -------------------------------------------------------------------------- */
/*                                   Images                                   */
/* -------------------------------------------------------------------------- */
struct ImagePool_t
{
    /* ----------------------- Add your image define here ----------------------- */

    // struct AppLauncher_t
    // {
    //     uint16_t app_icon[10000];
    //     // or
    //     uint16_t* app_icon = nullptr;
    // };
    // AppLauncher_t AppLauncher;

    struct StartupAnim_t
    {
        uint16_t warma_halftone[16384];
        uint16_t warma_halftone_width = 128;
        uint16_t warma_halftone_height = 128;
    };
    StartupAnim_t StartupAnim;
};
