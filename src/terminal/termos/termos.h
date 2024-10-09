
#ifndef TERMOS_H
#define TERMOS_H


/*** includes ***/

#include <termios.h>


/*** data ***/

typedef struct terminal {
    int screenrows;
    int screencols;
    struct termios orig_termios;
} terminal_t;


/*** rawmode ***/

extern void disable_rawmode(terminal_t *term_conf);
extern void enable_rawmode(terminal_t *term_conf);


/*** window ***/

extern void get_winsize(int *rows, int *cols);


#endif

