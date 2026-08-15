#include "config.h"
#include "json_manipulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

static Config global_config = {ENGLISH, 1};
static cJSON *config_json = NULL;

// Helper function to convert language string to enum
static Language string_to_language(const char *str) {
    if (str && (strcmp(str, "EN") == 0 || strcmp(str, "ENGLISH") == 0)) {
        return ENGLISH;
    }
    return FRENCH;
}

// Helper function to convert language enum to string
static const char* language_to_string(Language lang) {
    return lang == ENGLISH ? "EN" : "FR";
}

void load_config(void) {
    config_json = json_load_file("config.json");
    
    if (!config_json) {
        config_json = cJSON_CreateObject();
        save_config();
        return;
    }
    
    // Load language
    const char *lang_str = json_get_string(config_json, "language", "FR");
    global_config.language = string_to_language(lang_str);
    
    // Load settings
    cJSON *settings = cJSON_GetObjectItemCaseSensitive(config_json, "settings");
    if (settings) {
        global_config.template = json_get_bool(settings, "template", 1);
    }
}

void save_config(void) {
    // if (!config_json) {
    //     config_json = cJSON_CreateObject();
    // }
    
    // Update language (delete and recreate)
    cJSON *lang_item = cJSON_GetObjectItemCaseSensitive(config_json, "language");
    if (lang_item) {
        cJSON_DeleteItemFromObject(config_json, "language");
    }
    cJSON_AddStringToObject(config_json, "language", language_to_string(global_config.language));
    
    // Update settings
    cJSON *settings = cJSON_GetObjectItemCaseSensitive(config_json, "settings");
    if (!settings) {
        settings = cJSON_AddObjectToObject(config_json, "settings");
    }
    
    // Update auto_save (replace if exists)
    cJSON *auto_save = cJSON_GetObjectItemCaseSensitive(settings, "template");
    if (auto_save) {
        cJSON_DeleteItemFromObject(settings, "template");
    }
    cJSON_AddBoolToObject(settings, "template", global_config.template);
    
    // Write to file
    FILE *file = fopen("config.json", "w");
    if (file) {
        char *json_str = cJSON_Print(config_json);
        fprintf(file, "%s", json_str);
        fclose(file);
        free(json_str);
    } else {
        fprintf(stderr, "Warning: Could not save config.json\n");
    }
}

void cleanup_config(void) {
    if (config_json) {
        cJSON_Delete(config_json);
        config_json = NULL;
    }
}

Config* get_config(void) {
    return &global_config;
}

Language get_language_from_config(void) {
    return global_config.language;
}

void set_language_in_config(Language lang) {
    global_config.language = lang;
    save_config();
}
