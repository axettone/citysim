#include "random.h"
/** GLOBAL STUFF **/
random_status rng_status;

void init_random(){
    gsl_rng_env_setup();
    rng_status.T = gsl_rng_default;
    rng_status.r = gsl_rng_alloc (rng_status.T);
}
void teardown_random() {
    gsl_rng_free (rng_status.r);
}

double random_gaussian(const double sigma, const double mu) {
    return gsl_ran_gaussian (rng_status.r, sigma) + mu;
}