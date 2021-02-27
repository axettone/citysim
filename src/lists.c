#include "lists.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

cslist_t* cslist_alloc(size_t n) {
    cslist_t* list = (cslist_t*)malloc(sizeof(cslist_t) * n);
    if(list == NULL) {
        fprintf(stderr, "Cannot allocate memory\n");
        exit(1);
    }
    return list;
}