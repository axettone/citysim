#ifndef RANDOM_H
#define RANDOM_H

#include <gsl/gsl_rng.h>// GSL random number generators
#include <gsl/gsl_randist.h>// GSL random distributions

typedef struct {
    const gsl_rng_type * T;
    gsl_rng * r;
} random_status;


extern random_status rng_status;

void init_random();

void teardown_random();

double random_gaussian(const double sigma, const double mu);
double random_exponential(const double mu);
#endif