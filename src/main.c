
/*** TODO ***/

// make timer
// improve tsp
// make prettier


/*** includes ***/

#include <stdlib.h>
#include <unistd.h>

#include "error/die.h"
#include "conversions/conversions.h"
#include "data-structs/clist/clist.h"
#include "display/display.h"
#include "modes/modes.h"


/*** args ***/

void load_data(int argc, char *argv[]) {
    unsigned length  = argc > 1 ? str_to_uint(argv[1]) : MIN_DISPLAY_LEN;
    unsigned height  = argc > 2 ? str_to_uint(argv[2]) : MIN_DISPLAY_HEIGHT;
    unsigned delay   = argc > 3 ? str_to_uint(argv[3]) : DEFAULT_FLIP_DELAY;
    char    *charset = argc > 5 ? argv[5]              : DEFAULT_ALPHABET; 

    if (length > MAX_DISPLAY_LEN || length < MIN_DISPLAY_LEN)
        die("wrong length dimensions");

    if (height > MAX_DISPLAY_HEIGHT || height < MIN_DISPLAY_HEIGHT)
        die("wrong height dimensions");

    if (delay < 0)
        die("invalid delay argument");

    clist_make(length);
    display_make(length, height, delay, charset);
}


/*** driver ***/

int main(int argc, char *argv[]) {
    load_data(argc, argv);

    do {
        char c = 0;

        if ((read(STDIN_FILENO, &c, 1)) == -1)
            die("couldnt read from stdin");

        process_mode(c);
        match_mode(DEFAULT_PADDING_TYPE);
        
        display_update_state();
        display_print();

    } while (display_get_mode());

    return EXIT_SUCCESS;
}
