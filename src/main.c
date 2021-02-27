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

/** GLOBAL STUFF **/
game_t game;

void print_header() {
  printf("%s\n", PACKAGE_STRING);
  printf("=====================================\n");
}

void the_loop() {
    printf("Executed main loop.\n");
}



int main(int argc, char** argv) {

    time_t t;
    size_t n = 100;
    int choice;
    unsigned int loop_n = 0;

    srand((unsigned) time(&t));
	print_header();
    init_economy();
	print_taxes();
    
    game.commercials = allocate_n_commercials(n, true);
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
        printf("Loop: %u\n", loop_n++);
        
        printf("Press enter to continue, q to quit.\n");
        choice = getchar();
    } while (choice != 'q');

    printf("Commercial pressure: %d\n", compute_commercial_pressure(game.commercials));
	printf("Low Residential Demand: %d\n", game.rci_demand.residential_l);
	return 0;
}
