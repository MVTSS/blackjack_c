#ifndef TERM_H
#define TERM_H

void term_init(void);
void term_restore(void);

void term_move(int ligne, int col);
void term_hide_cursor(void);
void term_show_cursor(void);

void term_clear(void);
void term_clear_line(void);
void term_flush(void);

char term_getchar(void);
void wait_keypress(void);

#endif
