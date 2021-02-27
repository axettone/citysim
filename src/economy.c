#include "economy.h"
#include "defaults.h"
#include "game.h"

void init_economy() {

	game.rci_demand.commercial_l = RCI_DEMAND_COMMERCIAL_L;
	game.rci_demand.commercial_m = RCI_DEMAND_COMMERCIAL_M;
	game.rci_demand.commercial_h = RCI_DEMAND_COMMERCIAL_H;

	game.rci_demand.industrial_l = RCI_DEMAND_INDUSTRIAL_L;
	game.rci_demand.industrial_m = RCI_DEMAND_INDUSTRIAL_M
	game.rci_demand.industrial_h = RCI_DEMAND_INDUSTRIAL_H;

	game.rci_demand.residential_l = RCI_DEMAND_RESIDENTIAL_L;
	game.rci_demand.residential_m = RCI_DEMAND_RESIDENTIAL_M;
	game.rci_demand.residential_h = RCI_DEMAND_RESIDENTIAL_H;
	
	game.rci_taxes.commercial_l = DEFAULT_TAX_RATE;
	game.rci_taxes.commercial_m = DEFAULT_TAX_RATE;
	game.rci_taxes.commercial_h = DEFAULT_TAX_RATE;

	game.rci_taxes.industrial_l = DEFAULT_TAX_RATE;
	game.rci_taxes.industrial_m = DEFAULT_TAX_RATE;
	game.rci_taxes.industrial_h = DEFAULT_TAX_RATE;

	game.rci_taxes.residential_l = DEFAULT_TAX_RATE;
	game.rci_taxes.residential_m = DEFAULT_TAX_RATE;
	game.rci_taxes.residential_h = DEFAULT_TAX_RATE;

    game.economy_stats.budget = DEFAULT_INITIAL_BUDGET;
    game.economy_stats.GDP = 0;
}

void print_taxes () {
  printf("\t-=#TAXES!#=-\n");
  printf("RESIDENTIAL\nLow:\t%d%%\nMid:\t%d%%\nHigh:\t%d%%\n", 
    game.rci_taxes.residential_l,
    game.rci_taxes.residential_m,
    game.rci_taxes.residential_h);
    
    printf("COMMERCIAL\nLow:\t%d%%\nMid:\t%d%%\nHigh:\t%d%%\n", 
    game.rci_taxes.commercial_l,
    game.rci_taxes.commercial_m,
    game.rci_taxes.commercial_h);
    
    printf("INDUSTRIAL\nLow:\t%d%%\nMid:\t%d%%\nHigh:\t%d%%\n", 
    game.rci_taxes.industrial_l,
    game.rci_taxes.industrial_m,
    game.rci_taxes.industrial_h);
}

int compute_commercial_pressure(cslist_t *commercials) {
    cslist_t* cursor = commercials;
    int pressure = 0;
    while(cursor != NULL) {
        BLDG_COMMERCIAL* comm = (BLDG_COMMERCIAL*)(cursor->item);
        pressure += (int)(comm->employees);
        cursor = cursor->next;
    }
    return pressure;
}

int compute_commercial_gdp(cslist_t *commercials) {
    cslist_t* cursor = commercials;
    int gdp = 0;
    while(cursor != NULL) {
        BLDG_COMMERCIAL* bldg = (BLDG_COMMERCIAL*)(cursor->item);
        gdp += (int)(bldg->employees) * GDP_AVG_COMM_EMP;
        cursor = cursor->next;
    }
    return gdp;
}
int compute_industrial_gdp(cslist_t *industrials) {
    cslist_t* cursor = industrials;
    int gdp = 0;
    while(cursor != NULL) {
        BLDG_INDUSTRIAL* bldg = (BLDG_INDUSTRIAL*)(cursor->item);
        gdp += (int)(bldg->employees) * GDP_AVG_INDU_EMP;
        cursor = cursor->next;
    }
    return gdp;
}