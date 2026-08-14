#include "language.h"
#include "term_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Language current_language = FRENCH;

// Language packs (will be loaded from JSON)
Language_Pack french_pack = {0};
Language_Pack english_pack = {0};

// JSON documents (for cleanup)
static cJSON *french_json = NULL;
static cJSON *english_json = NULL;

// Helper function to load JSON from file
static cJSON* load_json_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Warning: Could not open file %s\n", filename);
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
        fprintf(stderr, "Warning: Invalid JSON in %s\n", filename);
        return NULL;
    }
    
    return json;
}

// Helper function to safely extract string from JSON
static const char* json_get_string(cJSON *obj, const char *key, const char *default_value) {
    cJSON *item = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (cJSON_IsString(item) && item->valuestring) {
        return item->valuestring;
    }
    return default_value;
}

// Function to populate Language_Pack from JSON
static void populate_language_pack(Language_Pack *pack, cJSON *json) {
    if (!json) return;
    
    // Menu section
    cJSON *menu = cJSON_GetObjectItemCaseSensitive(json, "menu");
    if (menu) {
        pack->menu_title = json_get_string(menu, "title", "");
        pack->menu_available_money = json_get_string(menu, "available_money", "");
        pack->menu_start_game = json_get_string(menu, "start_game", "");
        pack->menu_help = json_get_string(menu, "help", "");
        pack->menu_quit = json_get_string(menu, "quit", "");
        pack->menu_change_lang = json_get_string(menu, "change_lang", "");
        pack->menu_selection = json_get_string(menu, "selection", "");
    }
    
    // Help section
    cJSON *help = cJSON_GetObjectItemCaseSensitive(json, "help");
    if (help) {
        pack->help_title = json_get_string(help, "title", "");
        pack->help_rules_line1 = json_get_string(help, "rules_line1", "");
        pack->help_press_enter = json_get_string(help, "press_enter", "");
    }
    
    // Game section
    cJSON *game = cJSON_GetObjectItemCaseSensitive(json, "game");
    if (game) {
        pack->game_deck_info = json_get_string(game, "deck_info", "");
        pack->game_how_much_bet = json_get_string(game, "how_much_bet", "");
        pack->game_error_not_enough_money = json_get_string(game, "error_not_enough_money", "");
        pack->game_switching_deck = json_get_string(game, "switching_deck", "");
        pack->game_press_enter = json_get_string(game, "press_enter", "");
        pack->game_dealer = json_get_string(game, "dealer", "");
        pack->game_player = json_get_string(game, "player", "");
        pack->game_what_to_do = json_get_string(game, "what_to_do", "");
        pack->game_play_again = json_get_string(game, "play_again", "");
        pack->game_unknown_command = json_get_string(game, "unknown_command", "");
    }
}

void init_languages(void) {
    french_json = load_json_file("lang_fr.json");
    english_json = load_json_file("lang_en.json");
    
    populate_language_pack(&french_pack, french_json);
    populate_language_pack(&english_pack, english_json);
}

void cleanup_languages(void) {
    if (french_json) cJSON_Delete(french_json);
    if (english_json) cJSON_Delete(english_json);
}

void set_language(Language lang) {
    current_language = lang;
}

Language get_language(void) {
    return current_language;
}

Language_Pack* get_language_pack(void) {
    if (current_language == ENGLISH) {
        return &english_pack;
    }
    return &french_pack;
}

void menu_lang(void) {
    int input;
    
    term_clear();
    term_move(1, 1); printf("=== SELECT A LANGUAGE / CHOISIR UNE LANGUE ===\n");
    term_move(3, 1); printf("1: English");
    term_move(4, 1); printf("2: Français");
    term_move(6, 1); printf("Selection : ");
    term_flush();
    
    do {
        input = getchar();
        while (input == '\n' || input == '\r') {
            input = getchar();
        }
    } while (input == EOF);
    
    switch (input) {
        case '1':
            set_language(ENGLISH);
            break;
        case '2':
            set_language(FRENCH);
            break;
        default:
            // Default to current language
            break;
    }
    
    term_clear();
}
