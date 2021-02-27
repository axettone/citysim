#ifndef GAME_H
#define GAME_H
#include "lists.h"
#include "economy.h"

typedef struct {
    cslist_t *commercials;
    cslist_t *industrials;
    cslist_t *residentials;
    RCI rci_demand; 
    RCI rci_taxes;

} game_t;

extern game_t game;
#endif