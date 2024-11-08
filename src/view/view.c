

/*** includes ***/

#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "termgui/termgui.h"
#include "termos/termos.h"
#include "../error/die.h"

#include "view.h"


/*** state ***/

static terminal_t term_conf;
volatile sig_atomic_t winch_flag = 0;


/*** signals ***/

void winch_observer(int sig) {
    if (sig == SIGWINCH)
        winch_flag = 1;
}

void setup_signals(void) {
    struct sigaction sa;

    sa.sa_handler = winch_observer;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGWINCH, &sa, NULL) == -1)
        die("couldnt setup signals");
}


/*** terminal os ***/

void disable_rawmode_wrapper(void) {
    disable_rawmode(&term_conf);
}

void setup_rawmode(void) {
    enable_rawmode(&term_conf);

    atexit(disable_rawmode_wrapper);
}

void update_winsize(void) {
    get_winsize(&term_conf.screenrows, &term_conf.screencols);
}

int check_window_updates(void) {
    if (winch_flag) {
        update_winsize();
        winch_flag = 0;
        return 1;
    }
    return 0;
}


/*** terminal screen ***/

void format_screen(void) {
    printf("%s%s", FONT_BOLD, COLOR_WHITE);
}

void setup_screen(void) {
    set_screen();
    format_screen();
    update_winsize();

    atexit(reset_screen);
}


/*** methods ***/

void print_centered(const char *str, unsigned length, unsigned height) {
    if (check_window_updates())
        printf("%s", CLEAR_SCREEN);

    int center_row = round((term_conf.screenrows - height) / 2.0) + 1;
    int center_col = round((term_conf.screencols - length) / 2.0) + 1;

    for (unsigned i = 0; i < height; ++i) {
        printf("\x1b[%d;%dH%.*s",
                center_row + i, center_col, length, str + i * length);
    }
}

void pause_screen(int TIME) {
   fflush(stdout);
   usleep(TIME);
}

/*** setup ***/

void setup_terminal(void) {
    setup_rawmode();
    setup_screen();
    setup_signals();
}
