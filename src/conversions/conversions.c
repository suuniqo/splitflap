

/*** includes ***/

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "../error/die.h"


/*** conversions ***/

unsigned str_to_uint(char *str) {
    unsigned long res = strtoul(str, NULL, 10);

    if (res < 0 || res > UINT_MAX)
        die("cant convert to unsigned");

    return res;
}

void str_toupper(char *str) {
    for (unsigned i = 0; i < strlen(str); ++i)
        str[i] = toupper(str[i]);
}
