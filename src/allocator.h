#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include <lists.h>
#include <stdbool.h>

cslist_t* allocate_n_commercials(size_t n, bool fw_random);

#endif