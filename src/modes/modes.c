
/*** includes **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "../display/display.h"
#include "../data-structs/clist/clist.h"
#include "../error/die.h"

#include "modes.h"


/*** defines ***/

#define MATCH_DELAY 150

#define FORMAT_TIME_REDUCED "%R"
#define FORMAT_TIME_FULL "%T"

#define FORMAT_DATE_REDUCED "%H%M%S"


/*** process mode ***/

void process_mode(char mode) {
    if (mode == display_get_mode() || mode == 0)
        return;

    switch (mode) {
        case MODE_CHAIN:
        case MODE_RAND:
        case MODE_TIME:
        case MODE_DATE:
        case MODE_DAY:
        case MODE_QUIT:
            display_set_mode((display_mode_t)mode);
            break;
        default:
            display_set_mode(MODE_DEFAULT);
    }
}


/*** modes ***/

void mode_word(display_mode_t mode) {
    static int count = MATCH_DELAY;

    if (display_check_status() && !count--) {
        unsigned steps = 0;
        switch (mode) {
            case MODE_CHAIN:
                steps = 1;
                break;
            case MODE_RAND:
                steps = (unsigned)rand() % clist_get_len();
                break;
            default:
                die("mode doesn't exist");
        }

        while (steps--)
            clist_next_word();

        count = MATCH_DELAY;
    }
    display_set_target(clist_get_word());
}

void mode_time(display_mode_t mode) {
    time_t epoch_time;
    struct tm *date;

    char *format;
    char time_buff[display_get_length() + 1];

    time(&epoch_time);
    date = localtime(&epoch_time);

    switch (mode) {
        case MODE_TIME:
            if (display_get_length() < 8)
                format = "%H:%M";
            else
                format = "%H:%M:%S";
            break;
        case MODE_DAY:
            format = "%a%d";
            for (int i = 1; i < 3; i++) time_buff[i] -= 32;
            break;
        case MODE_DATE:
            format = "%d/%m";
            break;
        default:
            die("mode doesn't exist");
    }

    strftime(time_buff, display_get_length(), format, date);
    if (mode == MODE_DAY) {
        time_buff[1] = toupper(time_buff[1]);
        time_buff[2] = toupper(time_buff[2]);
    }

    display_set_target(time_buff);
}

void mode_quit(void) {
    static int count = MATCH_DELAY;
    display_set_target("ABORT");

    if (display_check_status() && !count--) {
        display_terminate();
    }
}

void mode_default(void) {
    display_set_target("INPUT");
}


/*** mode matcher ***/

void match_mode(void) {
    display_mode_t mode = display_get_mode();

    switch (mode) {
        case MODE_CHAIN:
        case MODE_RAND:
            mode_word(mode);
            break;
        case MODE_TIME:
        case MODE_DATE:
        case MODE_DAY:
            mode_time(mode);
            break;
        case MODE_QUIT:
            mode_quit();
            break;
        default:
            mode_default();
    }
}
