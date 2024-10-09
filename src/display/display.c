
/*** includes ***/

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../charset/alphabet.h"

#include "display.h"


/*** data ***/

typedef struct display_conf {
    unsigned length;
    unsigned flip_delay;
    char padding;
} display_conf_t;

typedef struct dispaca {
    char *state;
    char *target;
    display_mode_t mode;
    display_conf_t conf;
} display_t;


/*** state ***/

static display_t *splitflap;


/*** dispaca init ***/

void display_free(void) {
    free(splitflap->state);
    free(splitflap->target);
    free(splitflap);
}

void display_make(int length, int flip_delay, padding_t padding, char *charset) {
    char buff[length + 1];
    buff[length] = '\0';
    memset(buff, ' ', length);

    splitflap = malloc(sizeof(display_t));

    *splitflap = (display_t) {
        .state = strdup(buff),
        .target = strdup(buff),
        .mode = MODE_DEFAULT,
        .conf = (display_conf_t) {
            .length = length,
            .flip_delay = flip_delay,
            .padding = padding
        }
    };
    charset_init(charset);
    atexit(display_free);
}


/*** dispaca getters ***/

char *display_get_state(void) {
    return splitflap->state;
}

char display_get_mode(void) {
    return splitflap->mode;
}

int display_get_length(void) {
    return splitflap->conf.length;
}

int display_get_delay(void) {
    return splitflap->conf.flip_delay;
}

char *__display_get_target(void) {
    return splitflap->target;
}


/*** display setters ***/

void display_set_target(const char* target) {
    unsigned target_len = strlen(target);

    char padding[splitflap->conf.length + 1];
    memset(padding, ' ', splitflap->conf.length - target_len);
    padding[splitflap->conf.length - target_len] = '\0';

    unsigned padding_len = strlen(padding);
    unsigned padding_div;

    switch (splitflap->conf.padding) {
        case 'l':
            padding_div = padding_len;
            break;
        case 'c':
            padding_div = padding_len / 2;
            break;
        case 'r':
            padding_div = 0;
    }
    snprintf(splitflap->target, splitflap->conf.length + 1, "%.*s%s%.*s",
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


/*** dispaca methods ***/

void display_update_state(void) {
    for (unsigned i = 0; i < splitflap->conf.length; i++) {
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
