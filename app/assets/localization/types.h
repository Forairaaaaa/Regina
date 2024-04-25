/**
 * @file types.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "text_pool/text_pool_map.h"
#include "text_pool/text_pool_en.h"
#include "text_pool/text_pool_cn.h"
#include "text_pool/text_pool_jp.h"

/* -------------------------------------------------------------------------- */
/*                                 How to use                                 */
/* -------------------------------------------------------------------------- */
// 1) Edit localization.csv
// 2) python ./localization_2_type.py

/* -------------------------------------------------------------------------- */
/*                                  Text pool                                 */
/* -------------------------------------------------------------------------- */
struct TextPool_t
{
    TextPool_en_t TextEN;
    TextPool_cn_t TextCN;
    TextPool_jp_t TextJP;
};
