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
    // spdlog::info("system config:");
    // spdlog::info(" - brightness: {}", _config.brightness);
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
    // _config.brightness = doc["brightness"];

    free(file_content);
    spdlog::info("done");

    _config_check_valid();
}

void HAL_Regina::saveSystemConfig()
{
    spdlog::info("save config to fs");

    std::string json_content;
    {
        // Create json
        JsonDocument doc;

        _config_check_valid();

        // Copy
        // doc["brightness"] = _config.brightness;

        // Serialize
        if (serializeJson(doc, json_content) == 0)
        {
            _disp_init();
            popFatalError("Serialize failed");
        }
    }

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
