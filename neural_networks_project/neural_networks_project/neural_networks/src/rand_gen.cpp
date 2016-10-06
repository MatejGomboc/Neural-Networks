#include "rand_gen.h"
#include <random>

using namespace neural_networks;

rand_gen::rand_gen(void)
{
}


rand_gen::~rand_gen(void)
{
}


double rand_gen::clamp_value(double value)
{
	if (value >= max_double) return max_double;
	else if (value <= min_double) return min_double;
	else return value;
}


int rand_gen::clamp_value(int value)
{
	if (value >= max_int) return max_int;
	else if (value <= min_int) return min_int;
	else return value;
}


double rand_gen::random_double(void)
{
    return (min_double + ((double)rand() / (double)RAND_MAX) * (max_double - min_double));
}


double rand_gen::random_double(double min_val, double max_val)
{
    return (min_val + ((double)rand() / (double)RAND_MAX) * (max_val - min_val));
}


int rand_gen::random_int(void)
{
    return (min_int + (rand() / RAND_MAX) * (max_int - min_int));
}


int rand_gen::random_int(int min_val, int max_val)
{
    return (min_val + (rand() / RAND_MAX) * (max_val - min_val));
}