
/*** includes ***/

#include <unistd.h>
#include <sys/ioctl.h>

#include "../../error/die.h"

#include "termos.h"


/*** rawmode ***/

void disable_rawmode(terminal_t *term_conf) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_conf->orig_termios) == -1)
        die("couldnt disable raw mode");
}

void enable_rawmode(terminal_t *term_conf) {
    if (tcgetattr(STDIN_FILENO, &term_conf->orig_termios) == -1)
        die("couldnt get terminal attributes");

    struct termios raw_termios = term_conf->orig_termios;
    raw_termios.c_iflag &= ~(ICRNL | IXON);
    raw_termios.c_oflag &= ~(OPOST);
    raw_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw_termios.c_cc[VMIN] = 0;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios) == -1)
        die("couldnt enable raw mode");
}


/*** window ***/

void get_winsize(int *rows, int *cols) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
        die("could not get window size");

    *cols = ws.ws_col;
    *rows = ws.ws_row;
}

