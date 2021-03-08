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
#include "random.h"
#include "economymodels.h"

/** GLOBAL STUFF **/
game_t game;

#define START_WITH_N_COMMERCIALS 50

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
    game.com_workers = 0;
    game.ind_workers = 0;
    cslist_t* cursor = game.commercials;
    
    while(cursor != NULL) {
        BLDG_COMMERCIAL* bldg = (BLDG_COMMERCIAL*)(cursor->item);
        game.com_workers += (unsigned int)(bldg->employees);
        cursor = cursor->next;
    }

    cursor = game.industrials;

    while(cursor != NULL) {
        BLDG_INDUSTRIAL* bldg = (BLDG_INDUSTRIAL*)(cursor->item);
        game.ind_workers += (unsigned int)(bldg->employees);
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

    //Assumptions:
    //1) closed world (people don't go elsewhere and don't come from the outside)
    //2) Let's start with a little bit of unemployment (100 residential vs 40 + 20)
    
    computing_population();
    computing_workers();

    int primary_goods_pressure  = game.population * 0.20;
    //this should be higher for medium and higher wealth citizends
    int luxury_goods_pressure   = game.population * 0.05;

    //workers need products
    primary_goods_pressure += (game.ind_workers + game.com_workers) * 0.20;
    luxury_goods_pressure += (game.ind_workers + game.com_workers) * 0.01;

    int trading_pressure = primary_goods_pressure * 1 + luxury_goods_pressure * 2;

    printf("Population:\t%u\nInd.Workers:\t%u\nCom.Workers:\t%u\nUnemployment:%.2f%%\n",
        game.population,
        game.ind_workers,
        game.com_workers,
        100-100*((float)(game.ind_workers + game.com_workers)/game.population)
    );

    printf("Total industrial pressure:\t%d\nTotal trading pressure:\t\t%d\n",
        primary_goods_pressure+luxury_goods_pressure,
        trading_pressure
    );

    // Pressure effects

    //This should be a random picking, not a sequential picking.

    cslist_t* cursor = game.commercials;
    int distrib_pressure = trading_pressure / START_WITH_N_COMMERCIALS;
    while(cursor != NULL) {
        BLDG_COMMERCIAL* bldg = (BLDG_COMMERCIAL*)(cursor->item);
        int delta = bldg->capacity - bldg->employees;
        //bldg->employees += random_gaussian(delta, distrib_pressure*delta);
        cursor = cursor->next;
    }
    printf("Executed main loop.\n");
}



int main(int argc, char** argv) {

    time_t t;
    size_t n = 100;
    int choice;

    init_random();
    srand((unsigned) time(&t));

    game.year = 2000;
	print_header();
    init_economy();
	print_taxes();
    
    game.residentials = allocate_n_buildings(n, BLDG_TYPE_RESIDENTIAL, true);
    game.commercials = allocate_n_buildings(START_WITH_N_COMMERCIALS, BLDG_TYPE_COMMERCIAL, true);
    game.industrials = allocate_n_buildings(20, BLDG_TYPE_INDUSTRIAL, true);
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

    teardown_random();
	return 0;
}
