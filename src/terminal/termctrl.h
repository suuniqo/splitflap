
#ifndef TERMCTRL_H
#define TERMCTRL_H


/*** setup ***/

extern void setup_terminal(void);


/*** methods ***/

extern void print_centered(const char *str, unsigned length, unsigned height);
extern void pause_screen(int TIME);
extern char read_char(void);


#endif
