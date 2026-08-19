#ifndef CONFIG_H
#define CONFIG_H

#include "language.h"

typedef struct {
    Language language;
    int template;
} Config;

// Functions
void load_config(void);
void save_config(void);
void cleanup_config(void);
Config* get_config(void);
Language get_language_from_config(void);
void set_language_in_config(Language lang);

#endif
