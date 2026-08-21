#include "language.h"
#include "config.h"
#include "json_manipulation.h"
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

// Function to populate Language_Pack from JSON
static void populate_language_pack(Language_Pack *pack, cJSON *json) {
    if (!json) return;
    
    // Menu section
    cJSON *menu = cJSON_GetObjectItemCaseSensitive(json, "menu");
    if (menu) {
        pack->menu_early_leave = json_get_string(menu, "early_leave", "");
        pack->menu_title = json_get_string(menu, "title", "");
        pack->menu_available_money = json_get_string(menu, "available_money", "");
        pack->menu_start_game = json_get_string(menu, "start_game", "");
        pack->menu_help = json_get_string(menu, "help", "");
        pack->menu_quit = json_get_string(menu, "quit", "");
        pack->menu_change_lang = json_get_string(menu, "change_lang", "");
        pack->menu_selection = json_get_string(menu, "selection", "");
        pack->menu_bye = json_get_string(menu, "bye", "");
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
        pack->game_score_too_high = json_get_string(game, "score_too_high", "");
        pack->game_tie = json_get_string(game, "tie", "");
        pack->game_you_won = json_get_string(game, "you_won", "");
        pack->game_you_lost = json_get_string(game, "you_lost", "");
        pack->game_unknown_command = json_get_string(game, "unknown_command", "");
    }
    
    // Init Money section
    cJSON *init_money = cJSON_GetObjectItemCaseSensitive(json, "init_money");
    if (init_money) {
        pack->init_money_early_leave = json_get_string(init_money, "early_leave", "");
        pack->init_money_bank_already_exist = json_get_string(init_money, "bank_already_exist", "");
        pack->init_money_file_already_exist = json_get_string(init_money, "file_already_exist", "");
        pack->init_money_bank_doesnt_exist = json_get_string(init_money, "bank_doesnt_exist", "");
        pack->init_money_bank_loaded = json_get_string(init_money, "bank_loaded", "");
        pack->init_money_bankrupt = json_get_string(init_money, "bankrupt", "");
        pack->init_money_added_to_bank = json_get_string(init_money, "added_to_bank", "");
        pack->init_money_your_call = json_get_string(init_money, "your_call", "");
        pack->init_money_bye = json_get_string(init_money, "bye", "");
    }

    // Error section
    cJSON *error = cJSON_GetObjectItemCaseSensitive(json, "error");
    if (error) {
        pack->error_cant_load_file = json_get_string(error, "cant_load_file", "");
    }
}
    
void init_languages(void) {
    french_json = json_load_file("lang_fr.json");
    english_json = json_load_file("lang_en.json");
    
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
            set_language_in_config(ENGLISH);
            break;
        case '2':
            set_language_in_config(FRENCH);
            break;
        default:
            // Default to current language
            break;
    }
    
    wait_keypress();
    term_clear();
}
