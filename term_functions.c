#include <stdio.h>
#include "term_functions.h"
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797


void term_move(int line, int col) { printf("\033[%d;%dH", line, col); }

void term_hide_cursor(void) { printf("\033[?25l"); }
void term_show_cursor(void) { printf("\033[?25h"); }

void term_clear(void)      { printf("\033[2J\033[H"); }
void term_clear_actual_line(void) { printf("\033[2K"); }
void term_clear_line(int line) { term_move(line, 1); printf("\033[2K"); }
void term_flush(void)      { fflush(stdout); }

char term_getchar(void) { return getchar(); }




void _term_save_buffer(void) {
    printf("\033[?1049h"); // h = store term
    term_flush();
}

void _term_restore_buffer(void) {
    printf("\033[?1049l"); // l = buffer principal + restore curseur
    term_flush();
}


void wait_keypress(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* vide le buffer jusqu'au retour à la ligne */
    }
}




void term_init(void) {
    _term_save_buffer();
    term_show_cursor();
    term_clear();
    // term_hide_cursor();
}

void term_restore(void) {
    term_show_cursor();
    _term_restore_buffer();
}
