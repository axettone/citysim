#include "economymodels.h"

double norm_concurrency_pressure(double max, double x) {
    return -1*pow(x/max,4) + 1;
}