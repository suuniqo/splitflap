
/*** TODO ***/

// make timer
// improve tsp
// make prettier


/*** includes ***/

#include <stdlib.h>

#include "charset/alphabet.h"
#include "error/die.h"
#include "conversions/conversions.h"
#include "data-structs/clist/clist.h"
#include "display/display.h"
#include "modes/modes.h"
#include "terminal/termctrl.h"


/*** args ***/

void parse_args(int argc, char *argv[]) {
    unsigned length  = argc > 1 ? str_to_uint(argv[1]) : MIN_DISPLAY_LEN;
    unsigned height   = argc > 2 ? str_to_uint(argv[2]) : MIN_DISPLAY_HEIGHT;
    unsigned delay   = argc > 3 ? str_to_uint(argv[3]) : DEFAULT_FLIP_DELAY;
    char     padding = argc > 4 ? argv[4][0]           : DEFAULT_PADDING; 
    char    *charset = argc > 5 ? argv[5]              : DEFAULT_ALPHABET; 

    if (length > MAX_DISPLAY_LEN || length < MIN_DISPLAY_LEN)
        die("wrong length dimensions");

    if (height > MAX_DISPLAY_HEIGHT || height < MIN_DISPLAY_HEIGHT)
        die("wrong height dimensions");

    if (delay < 0)
        die("invalid delay argument");

    if (padding != PADDING_LEFT && padding != PADDING_CENTER && padding != PADDING_RIGHT)
        die("incorrect padding type");

    clist_make(length);
    display_make(length, height, delay, padding, charset);
}


/*** driver ***/

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    setup_terminal();

    do {
        process_mode(read_char());
        match_mode();
        
        display_update_state();
        print_centered(display_get_state(), display_get_length(), display_get_height());
        pause_screen(display_get_delay());

    } while (display_get_mode());

    return EXIT_SUCCESS;
}
