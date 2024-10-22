
/*** includes ***/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "../../error/die.h"

#include "clist.h"


/*** defines ***/

#define FILE_PATH_WORDLIST "assets/wordlist.txt"
#define FILE_PATH_DATELIST "assets/datelist.txt"

#define MAX_LINE_LEN 32
#define MAX_LIST_LEN 32768


/*** data ***/

typedef struct clist {
    node_t *cursor;
    unsigned len;
} clist_t;


/*** state ***/

static clist_t *clist = NULL;


/*** clist build ***/

void clist_load_file(FILE *word_file, unsigned long max_len) {
    char word[MAX_LINE_LEN] = "";

    do {
        fgets(word, MAX_LINE_LEN, word_file);
    } while (strlen(word) > max_len + 1 && word[0]);

    word[strlen(word) - 1] = '\0';
    clist->cursor = node_make(word[0] ? word : "ERROR");

    while (clist->len < MAX_LIST_LEN && fgets(word, MAX_LIST_LEN, word_file)) {
        if (strlen(word) <= max_len + 1) {
            word[strlen(word) - 1] = '\0';
            node_insert_end(clist->cursor, word);
            ++clist->len;
        }
    }
}

void clist_free(void) {
    node_t *curr = clist->cursor;

    while (curr->next != curr)
        node_remove_next(curr);
    node_free(curr);

    free(clist);
}

void clist_make(unsigned long max_len) {
    clist = malloc(sizeof(clist_t));

    FILE *word_file;
    if ((word_file = fopen(FILE_PATH_WORDLIST, "r")) == NULL)
        die("error accesing text file");

    clist_load_file(word_file, max_len);
    fclose(word_file);

    atexit(clist_free);
}


/*** clist getters ***/

int clist_get_len(void) {
    return clist->len;
}

char *clist_get_word(void) {
    return clist->cursor->word;
}


/*** clist methods ***/

void clist_next_word(void) {
    clist->cursor = clist->cursor->next;
}

void __clist_print(void) {
    node_t *node = clist->cursor;

    do {
        node = node->next;
        printf("\n%s", node->word);
    } while (node != clist->cursor);
}

