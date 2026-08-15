#include "json_manipulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to load JSON from file
cJSON* json_load_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Warning: Could not open file %s, one was created for you using defaults\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *buffer = (char *)malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Could not allocate memory\n");
        fclose(file);
        return NULL;
    }
    
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);
    
    cJSON *json = cJSON_Parse(buffer);
    free(buffer);
    
    if (!json) {
        fprintf(stderr, "Warning: Invalid JSON in %s, using defaults\n", filename);
        return NULL;
    }
    
    return json;
}

// Helper function to safely extract string from JSON
const char* json_get_string(cJSON *obj, const char *key, const char *default_value) {
    if (!obj) return default_value;
    cJSON *item = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (cJSON_IsString(item) && item->valuestring) {
        return item->valuestring;
    }
    return default_value;
}

// Helper function to safely extract bool from JSON
int json_get_bool(cJSON *obj, const char *key, int default_value) {
    if (!obj) return default_value;
    cJSON *item = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (cJSON_IsBool(item)) {
        return item->type == cJSON_True ? 1 : 0;
    }
    return default_value;
}
