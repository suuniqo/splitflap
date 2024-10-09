
/*** includes ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../error/die.h"

#include "node.h"


/*** node build ***/

node_t *node_make(const char* word) {
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->word = strdup(word);
    newNode->next = newNode;
    return newNode;
} 

void node_free(node_t *node_free) {
    free(node_free->word);
    free(node_free);
}


/*** node methods ***/

void node_insert_end(node_t *last, const char* word) {
    if (last == NULL)
        die("last is NULL");

    node_t *newNode = node_make(word);

    newNode->next = last->next;
    last->next = newNode;
}

void node_remove_next(node_t *curr) {
    if (curr->next == curr)
        return;

    node_t *node = curr->next; 
    curr->next = node->next;
    node_free(node);
}
