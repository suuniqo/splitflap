
#ifndef DISPLAY_H
#define DISPLAY_H

/*** defines ***/

#define SPLITFLAP_WIDTH 1

#define MIN_DISPLAY_LEN 5
#define MAX_DISPLAY_LEN 32

#define DEFAULT_FLIP_DELAY 15000

#define DEFAULT_PADDING 'r'


/*** data ***/

typedef enum {
    MODE_DEFAULT = '0',
    MODE_CHAIN,
    MODE_RAND,
    MODE_TIME,
    MODE_DATE,
    MODE_DAY,
    MODE_QUIT = 'Q',
    MODE_END = '\0'
} display_mode_t;


typedef enum {
    PADDING_RIGHT = 'r',
    PADDING_CENTER = 'c',
    PADDING_LEFT = 'l'
} padding_t;


/*** display init ***/

extern void display_make(int length, int flip_delay, padding_t padding, char *charset);


/*** display getters ***/

extern char *display_get_state(void);
extern char display_get_mode(void);

extern int display_get_length(void);
extern int display_get_delay(void);


/*** display setters ***/

extern void display_set_target(const char* target);
extern void display_set_mode(display_mode_t mode);


/*** display methods ***/

extern void display_update_state(void);
extern int display_check_status(void);
extern void display_terminate(void);


#endif
