/**
 * @file shared.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "shared.h"

SharedData* SharedData::_shared_data = nullptr;

SharedData* SharedData::Get() { return _shared_data; }

bool SharedData::Check() { return _shared_data != nullptr; }

bool SharedData::Inject(SharedData* sharedData)
{
    if (_shared_data != nullptr)
    {
        spdlog::error("SharedData already exist");
        return false;
    }

    if (sharedData == nullptr)
    {
        spdlog::error("invalid SharedData ptr");
        return false;
    }

    _shared_data = sharedData;

    spdlog::info("SharedData injected, type: {}", sharedData->type());

    return true;
}

void SharedData::Destroy()
{
    if (_shared_data == nullptr)
    {
        spdlog::error("SharedData not exist");
        return;
    }

    delete _shared_data;
    _shared_data = nullptr;
}
