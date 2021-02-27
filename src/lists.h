#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>

typedef void* cspointer;

typedef struct cslist {
    cspointer item;
    struct cslist* next;
} cslist_t;

cslist_t* cslist_alloc(size_t n);

#endif

