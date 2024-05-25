/**
 * @file hal_fs.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_regina.h"
#include "../hal_config.h"
#include <mooncake.h>
#include <string>
#include <ArduinoJson.h>
#include <dirent.h>
extern "C"
{
#include "../utils/wear_levelling/wear_levelling.h"
}

void HAL_Regina::_fs_init()
{
    spdlog::info("fs init");

    if (!fs_init())
    {
        _disp_init();
        popFatalError("Fs init failed");
    }

    loadSystemConfig();
    _log_out_system_config();
}

void HAL_Regina::_log_out_system_config()
{
    spdlog::info("system config:");
    spdlog::info(" - dialAPinSwaped: {}", _data.config.dialAPinSwaped);
    spdlog::info(" - dialBPinSwaped: {}", _data.config.dialBPinSwaped);
    spdlog::info(" - wifiSsid: {}", _data.config.wifiSsid);
    spdlog::info(" - wifiPassword: {}", _data.config.wifiPassword);
    spdlog::info(" - autoSleepTimeout: {}", _data.config.autoSleepTimeout);
    spdlog::info(" - mute: {}", _data.config.mute);
    spdlog::info(" - ringtone: {}", _data.config.ringtone);
}

/* -------------------------------------------------------------------------- */
/*                               Config realated                              */
/* -------------------------------------------------------------------------- */
static const char* _system_config_path = "/spiflash/system_config.json";

void HAL_Regina::_config_check_valid() { spdlog::info("check config valid"); }

void HAL_Regina::loadSystemConfig()
{
    spdlog::info("load config from fs");

    // Open file
    FILE* config_file = fopen(_system_config_path, "rb");

    // If not exist
    if (config_file == NULL)
    {
        spdlog::warn("{} not exist", _system_config_path);
        saveSystemConfig();
        return;
    }

    // Copy content
    char* file_content = 0;
    long file_length = 0;
    fseek(config_file, 0, SEEK_END);
    file_length = ftell(config_file);
    fseek(config_file, 0, SEEK_SET);
    file_content = (char*)malloc(file_length);
    if (!file_content)
    {
        _disp_init();
        popFatalError("Malloc failed");
    }
    fread(file_content, 1, file_length, config_file);
    fclose(config_file);

    // Parse
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file_content);
    if (error != DeserializationError::Ok)
    {
        free(file_content);
        // spdlog::error("json invaild");

        _disp_init();
        popWarning("Config JSON\nInvaild");

        saveSystemConfig();
        return;
    }

    // Copy
    if (!doc["mute"].isNull())
        _data.config.mute = doc["mute"];
    if (!doc["dialAPinSwaped"].isNull())
        _data.config.dialAPinSwaped = doc["dialAPinSwaped"];
    if (!doc["dialBPinSwaped"].isNull())
        _data.config.dialBPinSwaped = doc["dialBPinSwaped"];
    if (!doc["autoSleepTimeout"].isNull())
        _data.config.autoSleepTimeout = doc["autoSleepTimeout"];
    if (!doc["wifiSsid"].isNull())
        _data.config.wifiSsid = doc["wifiSsid"].as<std::string>();
    if (!doc["wifiPassword"].isNull())
        _data.config.wifiPassword = doc["wifiPassword"].as<std::string>();
    if (!doc["ringtone"].isNull())
        _data.config.ringtone = doc["ringtone"].as<std::string>();

    free(file_content);
    spdlog::info("done");

    _config_check_valid();
}

std::string HAL_Regina::_create_config_json()
{
    std::string json_content;
    // Create json
    JsonDocument doc;

    _config_check_valid();

    // Copy
    doc["mute"] = _data.config.mute;
    doc["dialAPinSwaped"] = _data.config.dialAPinSwaped;
    doc["dialBPinSwaped"] = _data.config.dialBPinSwaped;
    doc["autoSleepTimeout"] = _data.config.autoSleepTimeout;
    doc["wifiSsid"] = _data.config.wifiSsid;
    doc["wifiPassword"] = _data.config.wifiPassword;
    doc["ringtone"] = _data.config.ringtone;

    // Serialize
    if (serializeJson(doc, json_content) == 0)
    {
        _disp_init();
        popFatalError("Serialize failed");
    }
    return json_content;
}

void HAL_Regina::saveSystemConfig()
{
    spdlog::info("save config to fs");

    std::string json_content = _create_config_json();

    // Open file
    spdlog::info("open {}", _system_config_path);
    FILE* config_file = fopen(_system_config_path, "wb");
    if (config_file == NULL)
    {
        _disp_init();
        popFatalError("Open config failed");
    }

    // Write and save
    fputs(json_content.c_str(), config_file);
    fclose(config_file);

    spdlog::info("config saved: {}", _system_config_path);
}

std::vector<std::string> HAL_Regina::_ls(const std::string& path)
{
    spdlog::info("ls {}", path);

    std::vector<std::string> result;

    auto folder = opendir(path.c_str());

    // If no directory
    if (folder == NULL)
    {
        return result;
    }

    // Iterate all rec files
    struct dirent* entry;
    while ((entry = readdir(folder)) != NULL)
    {
        // pass
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Get file name
        result.push_back(entry->d_name);
    }

    // Close folder
    closedir(folder);

    return result;
}
