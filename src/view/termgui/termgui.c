
/*** includes ***/

#include <stdio.h>

#include "termgui.h"


/*** screen ***/

void set_screen(void) {
    printf("\n%s%s%s\n", CLEAR_SCREEN, CURSOR_RESET, CURSOR_HIDE);
}

void reset_screen(void) {
    printf("%s%s", COLOR_RESET, CURSOR_SHOW);
}
