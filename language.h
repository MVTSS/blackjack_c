#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <cjson/cJSON.h>

typedef enum {
    FRENCH = 0,
    ENGLISH = 1
} Language;

typedef struct {
    // Menu
    const char *menu_title;
    const char *menu_available_money;
    const char *menu_start_game;
    const char *menu_help;
    const char *menu_quit;
    const char *menu_change_lang;
    const char *menu_selection;
    
    // Help
    const char *help_title;
    const char *help_rules_line1;
    const char *help_press_enter;
    
    // Game
    const char *game_deck_info;
    const char *game_how_much_bet;
    const char *game_error_not_enough_money;
    const char *game_switching_deck;
    const char *game_press_enter;
    const char *game_dealer;
    const char *game_player;
    const char *game_what_to_do;
    const char *game_play_again;
    const char *game_unknown_command;
    
    // Init Money
    const char *init_money_early_leave;
    const char *init_money_bank_already_exist;
    const char *init_money_file_already_exist;
    const char *init_money_bank_doesnt_exist;
    const char *init_money_bank_loaded;
    const char *init_money_bankrupt;
    const char *init_money_added_to_bank;
    const char *init_money_your_call;
    const char *init_money_bye;
} Language_Pack;

// Global variable
extern Language current_language;

// Functions
void init_languages(void);
void set_language(Language lang);
Language get_language(void);
Language_Pack* get_language_pack(void);
void menu_lang(void);
void cleanup_languages(void);

#endif
