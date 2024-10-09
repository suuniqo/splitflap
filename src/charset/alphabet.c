
/*** includes ***/

#include <_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../error/die.h"

#include "alphabet.h"


/*** defines ***/

#define ASCII_LEN 128


/*** data ***/

typedef struct charset {
    unsigned char charjumps[ASCII_LEN];
    unsigned len;
} charset_t;


/*** state ***/

static charset_t *alphabet;


/*** processing ***/

int isvalid_ascii(char c) {
    return c >= ' ' && c <= '~';
}

void clean_charset(char *charset) {
    unsigned len = strlen(charset), pos = 0;

    unsigned char hashmap[ASCII_LEN]; memset(hashmap, 0, ASCII_LEN);
    char buff[len + 1]; memset(buff, '\0', len + 1);

    for (unsigned i = 0; i < len; ++i) {
        unsigned char c = charset[i];
        if (isvalid_ascii(c) && !hashmap[c]) {
            buff[pos++] = c;
            hashmap[c] = 1;
        }
    }
    if (pos < len)
        snprintf(charset, pos + 1, "%s", buff);
}


/*** init ***/

void free_charset(void) {
    free(alphabet);
}

void charset_init(char *charset) {
    clean_charset(charset);
    alphabet = malloc(sizeof(charset_t));

    memset(alphabet->charjumps, '\0', ASCII_LEN);
    unsigned len = alphabet->len = strlen(charset);

    for (unsigned i = 0; i < len; ++i)
        alphabet->charjumps[(unsigned char)charset[i]] = charset[(i + 1) % len];

    atexit(free_charset);
}


/*** alphabet ***/

int is_alphabet(unsigned char c) {
    return isvalid_ascii(c) && alphabet->charjumps[c];
}

int str_is_alphabet(char *str) {
    unsigned i = 0, len = strlen(str);

    while (i < len && is_alphabet(str[i]))
        ++i;

    return i == strlen(str);
}


/*** getters ***/

int get_alphabet_length(void) {
    return alphabet->len;
}

char get_next_char(unsigned char c) {
    if (!is_alphabet(c))
        return '%';

    return alphabet->charjumps[c];
}


/*** distance ***/

 int get_char_dist(char c1, char c2) {
     if (!is_alphabet(c1) || !is_alphabet(c2))
         die("cannot get dist between non-alphabet chars");

     int char_dist = 0;

     while ((c1 != c2)) {
         c1 = get_next_char(c1);
         char_dist++;
     }
     return char_dist;
 }

int get_word_dist(const char* str1, const char* str2) {
    int word_dist = 0;
    int hamm_dist = 0;

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int max_len = len1 > len2 ? len1 : len2;

    for (int i = 0; i < max_len; ++i) {

        char c1 = i < len1 ? str1[i] : ' '; 
        char c2 = i < len2 ? str2[i] : ' '; 

        if (c1 != c2) {
            word_dist += get_char_dist(c1, c2);
            hamm_dist++;
        }
    }
    return hamm_dist * word_dist;
}
