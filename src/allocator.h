#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include "lists.h"
#include <stdbool.h>
#include "buildings.h"

cslist_t* allocate_n_buildings(size_t n, int building_type, bool fw_random);

#endif