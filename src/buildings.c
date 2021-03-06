#include "buildings.h"
#include "random.h"

void set_default_easiness(easiness_t* easiness){
  easiness->crime = 20;
  easiness->pollution = 10;
  easiness->fire_hazard = 10;
}

void print_easiness(easiness_t* easiness) {
  printf("Crime:\t\t%d/100\nPollution:\t%d/100\nFire hazard:\t%d/100\n",
    easiness->crime,
    easiness->pollution,
    easiness->fire_hazard);
}

void print_commercial_data(BLDG_COMMERCIAL* bldg) {
    printf("id:\t\t%d\nskin:\t\t%d\ncapacity:\t\t%d\nemployees:\t\t%d\n",
        bldg->id,
        bldg->skin,
        bldg->capacity,
        bldg->employees
    );
}

BLDG_COMMERCIAL* create_commercial_building(unsigned int id, bool fw_random) {
	BLDG_COMMERCIAL* ret = (BLDG_COMMERCIAL*)malloc(sizeof(BLDG_COMMERCIAL));
	ret->id = id;
	set_default_easiness(&ret->ease);

    
	
    if(fw_random){
        ret->skin = 1+rand() %(UINT8_MAX - 1);        
        ret->capacity =  ceil(random_exponential(0.666)*25);
        ret->employees = ceil((1-random_exponential(1)) * ret->capacity);
    }

	if (ret == NULL) {
		fprintf(stderr, "Wow, there's something wrong with memory\n");
		exit(1);
	}
	return ret;
}

BLDG_RESIDENTIAL* create_residential_building(unsigned int id, bool fw_random) {
	BLDG_RESIDENTIAL* ret = (BLDG_RESIDENTIAL*)malloc(sizeof(BLDG_RESIDENTIAL));
	ret->id = id;
	set_default_easiness(&ret->ease);
	
    if(fw_random){
        ret->skin = 1+rand() %(UINT8_MAX - 1);        
        ret->capacity =  ceil(random_exponential(0.5)*50);
        ret->residents = ceil((1-random_exponential(1))* ret->capacity);
    }

	if (ret == NULL) {
		fprintf(stderr, "Wow, there's something wrong with memory\n");
		exit(1);
	}
	return ret;
}

BLDG_INDUSTRIAL* create_industrial_building(unsigned int id, bool fw_random) {
	BLDG_INDUSTRIAL* ret = (BLDG_INDUSTRIAL*)malloc(sizeof(BLDG_INDUSTRIAL));
	ret->id = id;
	set_default_easiness(&ret->ease);
	
    if(fw_random){
        ret->skin = 1+rand() %(UINT8_MAX - 1);        
        ret->capacity =  ceil(random_exponential(0.5)*500);
        ret->employees = ceil((1-random_exponential(1))* ret->capacity);
    }

	if (ret == NULL) {
		fprintf(stderr, "Wow, there's something wrong with memory\n");
		exit(1);
	}
	return ret;
}


