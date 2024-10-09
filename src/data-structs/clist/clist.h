

#ifndef CLIST_H
#define CLIST_H


/*** includes ***/

#include "node.h"


/*** clist init  ***/

extern void clist_make(unsigned long max_len);


/*** clist getters ***/

extern int clist_get_len(void);
extern char *clist_get_word(void);


/*** clist methods ***/

extern void clist_next_word(void);
extern void _clist_print(void);


#endif
