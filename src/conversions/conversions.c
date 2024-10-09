

/*** includes ***/

#include <limits.h>
#include <stdlib.h>

#include "../error/die.h"


/*** conversions ***/

unsigned str_to_uint(char *str) {
    unsigned long res = strtoul(str, NULL, 10);

    if (res < 0 || res > UINT_MAX)
        die("cant convert to unsigned");

    return res;
}
