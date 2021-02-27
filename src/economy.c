#include "economy.h"
#include "defaults.h"
#include "game.h"

void init_economy() {

	game.rci_demand.commercial_l = RCI_DEMAND_COMMERCIAL_L;
	game.rci_demand.commercial_m = RCI_DEMAND_COMMERCIAL_M;
	game.rci_demand.commercial_h = RCI_DEMAND_COMMERCIAL_H;

	game.rci_demand.industrial_l = 10;
	game.rci_demand.industrial_m = 5;
	game.rci_demand.industrial_h = 1;

	game.rci_demand.residential_l = 10;
	game.rci_demand.residential_m = 5;
	game.rci_demand.residential_h = 1;
	
	game.rci_taxes.commercial_l = DEFAULT_TAX_RATE;
	game.rci_taxes.commercial_m = DEFAULT_TAX_RATE;
	game.rci_taxes.commercial_h = DEFAULT_TAX_RATE;

	game.rci_taxes.industrial_l = DEFAULT_TAX_RATE;
	game.rci_taxes.industrial_m = DEFAULT_TAX_RATE;
	game.rci_taxes.industrial_h = DEFAULT_TAX_RATE;

	game.rci_taxes.residential_l = DEFAULT_TAX_RATE;
	game.rci_taxes.residential_m = DEFAULT_TAX_RATE;
	game.rci_taxes.residential_h = DEFAULT_TAX_RATE;
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