#ifndef GAME_H
#define GAME_H

#include <inttypes.h>
#include "lists.h"
#include "economy.h"
#include "government.h"

typedef struct {
    cslist_t *commercials;
    cslist_t *industrials;
    cslist_t *residentials;
    RCI rci_demand; 
    RCI rci_taxes;

    ORDINANCES ordinances;

    ECONOMY_STATS economy_stats;
    uint16_t year;

    // These should be _l, _m, _h
    unsigned int population;
    unsigned int ind_workers;
    unsigned int com_workers;

} game_t;

extern game_t game;
#endif