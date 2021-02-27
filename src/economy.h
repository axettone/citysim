#ifndef ECONOMY_H
#define ECONOMY_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lists.h"
#include "buildings.h"


typedef struct {
	uint8_t	commercial_l;
	uint8_t	commercial_m;
	uint8_t	commercial_h;

	uint8_t	industrial_l;
	uint8_t industrial_m;
	uint8_t	industrial_h;

	uint8_t	residential_l;
	uint8_t	residential_m;
	uint8_t	residential_h;
} RCI;

void init_economy();
void print_taxes ();

int compute_commercial_pressure(cslist_t *commercials);
#endif
