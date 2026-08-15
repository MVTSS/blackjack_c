#ifndef JSON_MANIPULATION_H
#define JSON_MANIPULATION_H

#include <cjson/cJSON.h>

// Helper function to load JSON from file
cJSON* json_load_file(const char *filename);

// Helper function to safely extract string from JSON
const char* json_get_string(cJSON *obj, const char *key, const char *default_value);

// Helper function to safely extract bool from JSON
int json_get_bool(cJSON *obj, const char *key, int default_value);

#endif
