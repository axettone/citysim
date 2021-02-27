#include <stdlib.h>
#include <stdbool.h>
#include "allocator.h"
#include "lists.h"
#include "buildings.h"

cslist_t* allocate_n_commercials(size_t n, bool fw_random) {
    cslist_t* ret = cslist_alloc(n);
    cslist_t* cursor = ret;
    for(size_t i=0;i<n;i++) {
        BLDG_COMMERCIAL* item = create_commercial_building(i, fw_random);
        cursor->item = item;
        cursor->next = NULL;
        if(i<n-1) {
            cslist_t* tmp = cursor;
            cursor++;
            tmp->next = cursor;
        }
    }
    return ret;
}