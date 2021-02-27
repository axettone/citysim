#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
	uint8_t		crime;
	uint8_t		pollution;
	uint8_t		fire_hazard;
} easiness_t;

/**
 *  Commercial buildings 
 *
 *  skin:		    Reserved for UI times...
 *  capacity:		How many employees can work in this building.
 *  employeers:	How many employees work here
 *  ease:		    How good people feel here (services, pollution, etc.)
 *  business:		How the business is going
 *
 */

typedef struct {
	unsigned int 	id;
	uint8_t		skin;
	uint8_t		capacity;
	uint8_t		employees;
	easiness_t	ease;
	
} BLDG_COMMERCIAL;

typedef struct {
	unsigned int	id;
	uint8_t		skin;
	uint8_t		capacity;
	uint8_t		employees;
	easiness_t	ease;
	uint8_t		pollution;
} BLDG_INDUSTRIAL;

typedef struct {
	unsigned int	id;
	uint8_t		skin;
	uint8_t		capacity;
	uint8_t		residents;
	easiness_t	easiness;	
} BLDG_RESIDENTIAL;


/* FUNCTION DECLARATIONS */

BLDG_COMMERCIAL* create_commercial_building(unsigned int id, bool fw_random);
void print_easiness(easiness_t* easiness);
void print_commercial_data(BLDG_COMMERCIAL* bldg);
void set_default_easiness(easiness_t* easiness);

#endif