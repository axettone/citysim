#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#include <unistd.h>
#include <time.h>
#include "buildings.h"
#include "economy.h"
#include "lists.h"
#include "allocator.h"
#include "game.h"
#include "csvexport.h"

/** GLOBAL STUFF **/
game_t game;

void print_header() {
  printf("%s\n", PACKAGE_STRING);
  printf("_________ .__  __           _________.__         \n");
  printf("\\_   ___ \\|__|/  |_ ___.__./   _____/|__| _____  \n");
  printf("/    \\  \\/|  \\   __<   |  |\\_____  \\ |  |/     \\ \n");
  printf("\\     \\___|  ||  |  \\___  |/        \\|  |  Y Y  \\\n");
  printf(" \\______  /__||__|  / ____/_______  /|__|__|_|  /\n");
  printf("        \\/          \\/            \\/          \\/ \n");
}

void computing_population() {
    cslist_t* cursor = game.residentials;
    game.population = 0;
    while(cursor != NULL) {
        BLDG_RESIDENTIAL* bldg = (BLDG_RESIDENTIAL*)(cursor->item);
        game.population += (unsigned int)(bldg->residents);
        cursor = cursor->next;
    }
}

void computing_workers() {
    game.workers = 0;
    cslist_t* cursor = game.commercials;
    
    while(cursor != NULL) {
        BLDG_COMMERCIAL* bldg = (BLDG_COMMERCIAL*)(cursor->item);
        game.workers += (unsigned int)(bldg->employees);
        cursor = cursor->next;
    }

    cursor = game.industrials;

    while(cursor != NULL) {
        BLDG_INDUSTRIAL* bldg = (BLDG_INDUSTRIAL*)(cursor->item);
        game.workers += (unsigned int)(bldg->employees);
        cursor = cursor->next;
    }
}

void the_loop() {
    game.year++;

    /** GDP AND TAXES ON BUSINESS **/
    int comm_gdp = compute_commercial_gdp(game.commercials);
    int indu_gdp = compute_industrial_gdp(game.industrials);
    game.economy_stats.GDP = comm_gdp + indu_gdp;
    
    game.economy_stats.tax_income = comm_gdp/100 * game.rci_taxes.commercial_m
                                +   indu_gdp/100 * game.rci_taxes.industrial_m;

    game.economy_stats.budget += game.economy_stats.tax_income;
    game.economy_stats.budget -= government_costs(game.economy_stats.GDP);

    /** ECONOMY PRESSURES  **/

    //Computing population
    computing_population();
    computing_workers();

    printf("Executed main loop.\n");
}



int main(int argc, char** argv) {

    time_t t;
    size_t n = 100;
    int choice;

    srand((unsigned) time(&t));

    game.year = 2000;
	print_header();
    init_economy();
	print_taxes();
    
    game.residentials = allocate_n_buildings(n, BLDG_TYPE_RESIDENTIAL, true);
    game.commercials = allocate_n_buildings(n, BLDG_TYPE_COMMERCIAL, true);
    game.industrials = allocate_n_buildings(n, BLDG_TYPE_INDUSTRIAL, true);
    cslist_t* cursor = game.commercials;
/*    for(size_t i=0;i<n;i++) {
        BLDG_COMMERCIAL* item = (BLDG_COMMERCIAL*)cursor->item;        
	    print_easiness(&(item->ease));
        print_commercial_data(item);
        cursor = cursor->next;
    }*/

    do {
        sleep(1);
        the_loop();
        export_to_csv("./data.csv");
        printf("Year: %u\n", game.year);
        
        printf("Press enter to continue, q to quit.\n");
        choice = getchar();
    } while (choice != 'q');

    printf("Commercial pressure: %d\n", compute_commercial_pressure(game.commercials));
	printf("Low Residential Demand: %d\n", game.rci_demand.residential_l);
	return 0;
}
