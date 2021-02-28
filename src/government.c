#include "government.h"

int government_costs(int GDP) {
    //game game.economy_stats.GDP
    return GDP*0.33; //Simplicistic model: state costs 33% of GDP
}