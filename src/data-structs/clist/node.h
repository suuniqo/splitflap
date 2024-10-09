
#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H


/*** data ***/

typedef struct node {
    char *word;
    struct node *next;
} node_t;


/*** node build ***/

extern node_t *node_make(const char* word);
extern void node_free(node_t *node_free);


/*** node methods ***/

extern void node_insert_end(node_t *last, const char* word);
extern void node_remove_next(node_t *curr);


#endif
