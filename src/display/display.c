
/*** includes ***/

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "charset/alphabet.h"
#include "../view/view.h"

#include "display.h"


/*** data ***/

typedef struct display_conf {
    unsigned length;
    unsigned height;
    unsigned flip_delay;
} display_conf_t;

typedef struct display {
    char *state;
    char *target;
    display_mode_t mode;
    display_conf_t conf;
} display_t;


/*** state ***/

static display_t *splitflap;


/*** display init ***/

void display_free(void) {
    free(splitflap->state);
    free(splitflap->target);
    free(splitflap);
}

void display_make(unsigned length, unsigned height, unsigned flip_delay, char *charset) {
    char buff[length * height + 1];
    memset(buff, ' ', length * height);
    buff[length * height] = '\0';

    splitflap = malloc(sizeof(display_t));

    *splitflap = (display_t) {
        .state = strdup(buff),
        .target = strdup(buff),
        .mode = MODE_DEFAULT,
        .conf = (display_conf_t) {
            .length = length,
            .height = height,
            .flip_delay = flip_delay,
        }
    };
    charset_init(charset);
    setup_terminal();
    atexit(display_free);
}


/*** display getters ***/

char *display_get_state(void) {
    return splitflap->state;
}

char display_get_mode(void) {
    return splitflap->mode;
}

int display_get_length(void) {
    return splitflap->conf.length;
}
int display_get_height(void) {
    return splitflap->conf.height;
}

int display_get_delay(void) {
    return splitflap->conf.flip_delay;
}

char *__display_get_target(void) {
    return splitflap->target;
}


/*** display setters ***/

void display_set_target(const char* target, char padding_type) {
    unsigned target_len = strlen(target);
    unsigned padding_len = (splitflap->conf.length * splitflap->conf.height) - target_len ;

    char padding[padding_len + 1];
    memset(padding, ' ', padding_len);
    padding[padding_len] = '\0';

    unsigned padding_div;
    unsigned middle_row = (splitflap->conf.height / 2) * splitflap->conf.length;

    switch (padding_type) {
        case PADDING_LEFT:
            padding_div = middle_row + splitflap->conf.length - target_len;
            break;
        case PADDING_RIGHT:
            padding_div = middle_row;
            break;
        default:
            padding_div = middle_row + (splitflap->conf.length - target_len) / 2;
    }
    snprintf(splitflap->target, splitflap->conf.length * splitflap->conf.height + 1, "%.*s%s%.*s",
            padding_div, padding, target, padding_len - padding_div, padding);
}

void display_set_mode(display_mode_t mode) {
    switch (mode) {
        case MODE_CHAIN:
        case MODE_RAND:
        case MODE_TIME:
        case MODE_DATE:
        case MODE_DAY:
        case MODE_QUIT:
            splitflap->mode = mode;
            break;
        default:
            splitflap->mode = MODE_DEFAULT;
    }
}


/*** display methods ***/

void display_update_state(void) {
    for (unsigned i = 0; i < splitflap->conf.length * splitflap->conf.height; i++) {
        if (splitflap->state[i] != splitflap->target[i]) {
            splitflap->state[i] = get_next_char(splitflap->state[i]);
        }
    }
}

int display_check_status(void) {
    return !strcmp(splitflap->target, splitflap->state);
}

void display_terminate(void) {
    if (splitflap->mode == MODE_QUIT)
        splitflap->mode = MODE_END;
}

void display_print(void) {
    print_centered(display_get_state(), display_get_length(), display_get_height());
    pause_screen(display_get_delay());
}
