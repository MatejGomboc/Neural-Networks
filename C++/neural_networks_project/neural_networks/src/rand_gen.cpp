#include "rand_gen.h"
#include "constants.h"
#include <random>

namespace neural_networks
{
	static std::random_device generator; // Use a hardware entropy source if available, otherwise use PRNG

	// return random double value between max and min double value that can be generated
	double random_double(void)
	{
		std::uniform_real_distribution<double> distribution(min_double, max_double);
		return distribution(generator);
	}


	// return random double value between given max and min double values
	double random_double(const double min_val, const double max_val)
	{
		std::uniform_real_distribution<double> distribution(min_val, max_val);
		return distribution(generator);
	}


	// return random int value between max and min int value that can be generated
	int random_int(void)
	{
		std::uniform_int_distribution<int> distribution(min_int, max_int);
		return distribution(generator);
	}


	// return random int value between given max and min int values
	int random_int(const int min_val, const int max_val)
	{
		std::uniform_int_distribution<int> distribution(min_val, max_val);
		return distribution(generator);
	}
};