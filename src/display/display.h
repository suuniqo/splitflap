
#ifndef DISPLAY_H
#define DISPLAY_H

/*** defines ***/

#define MIN_DISPLAY_LEN 5
#define MAX_DISPLAY_LEN 64

#define MIN_DISPLAY_HEIGHT 1
#define MAX_DISPLAY_HEIGHT 64

#define DEFAULT_FLIP_DELAY 15000
#define DEFAULT_PADDING_TYPE 'c'
#define DEFAULT_ALPHABET " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"


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

extern void display_make(unsigned length, unsigned height, unsigned flip_delay, char *charset);


/*** display getters ***/

extern char *display_get_state(void);
extern char display_get_mode(void);

extern int display_get_length(void);
extern int display_get_height(void);
extern int display_get_delay(void);


/*** display setters ***/

extern void display_set_target(const char* target, char padding_type);
extern void display_set_mode(display_mode_t mode);


/*** display methods ***/

extern void display_update_state(void);
extern int display_check_status(void);
extern void display_terminate(void);
extern void display_print(void);


#endif
