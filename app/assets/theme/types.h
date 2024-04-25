/**
 * @file theme.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <cstdint>

/* -------------------------------------------------------------------------- */
/*                                   Colors                                   */
/* -------------------------------------------------------------------------- */
struct ColorPool_t
{
    /* ----------------------- Add your theme define here ----------------------- */

    struct Misc_t
    {
        uint32_t bgPopFatalError = 0x0078d7;
        uint32_t bgPopWarning = 0xFE8B00;
        uint32_t bgPopSuccess = 0x009653;
    };
    Misc_t Misc;
};
