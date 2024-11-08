

/*** includes ***/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../view/termgui/termgui.h"

#include "die.h"


/*** error ***/

void die(const char *err) {
    write(STDOUT_FILENO, COLOR_RED, sizeof(COLOR_RED));
    perror(err);
    write(STDOUT_FILENO, COLOR_RESET, sizeof(COLOR_RESET));

    exit(EXIT_FAILURE);
}
