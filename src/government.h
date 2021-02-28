#ifndef GOVERNMENT_H
#define GOVERNMENT_H

#include <stdbool.h>


typedef struct {
    bool LEGALIZE_GAMBLING;

    bool FREE_CLINICS;
    bool CLEAN_AIR_ACT;

} ORDINANCES;

typedef struct {
    int police_department;
    int fire_deparment;
    int military;
    int healthcare_system;
    int administration;

} GOVERNMENT_BUDGET;

int government_costs(int GDP);

#endif