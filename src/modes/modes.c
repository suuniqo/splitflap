
/*** includes **/

#include <stdlib.h>
#include <time.h>

#include "../display/display.h"
#include "../conversions/conversions.h"
#include "../data-structs/clist/clist.h"
#include "../error/die.h"

#include "modes.h"


/*** defines ***/

#define MATCH_DELAY 150


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

char *mode_word(display_mode_t mode) {
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
    return clist_get_word();
}

char *mode_time(display_mode_t mode) {
    time_t epoch_time;
    struct tm *date;

    char *format;
    unsigned display_len = display_get_length();
    static char time_buff[MAX_DISPLAY_LEN + 1];

    time(&epoch_time);
    date = localtime(&epoch_time);

    switch (mode) {
        case MODE_TIME:
            format = display_len < 8 ? "%R" : "%T";
            break;
        case MODE_DAY:
            format = display_len < 10 ? "%a%d" : "%A %d";
            break;
        case MODE_DATE:
            format = display_len < 7 ? "%d/%m" : "%D"; 
            break;
        default:
            die("mode doesn't exist");
    }

    strftime(time_buff, display_len, format, date);
    str_toupper(time_buff);

    return time_buff;
}

char *mode_quit(void) {
    static int count = MATCH_DELAY;

    if (display_check_status() && !count--) {
        display_terminate();
    }

    return "ABORT";
}

char *mode_default(void) {
    return "INPUT";
}


/*** mode matcher ***/

char *switch_mode(void) {
    display_mode_t mode = display_get_mode();
    switch (mode) {
        case MODE_CHAIN:
        case MODE_RAND:
            return mode_word(mode);
        case MODE_TIME:
        case MODE_DATE:
        case MODE_DAY:
            return mode_time(mode);
        case MODE_QUIT:
            return mode_quit();
        default:
            return mode_default();
    }
}

void match_mode(char padding_type) {
    display_set_target(switch_mode(), padding_type);
}
