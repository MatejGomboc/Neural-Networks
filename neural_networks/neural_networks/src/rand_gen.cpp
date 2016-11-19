#include "rand_gen.h"
#include "constants.h"
#include <random>

namespace Neural_networks
{
	static std::random_device generator; // use a hardware entropy source if available, otherwise use PRNG

	// return random double value between max and min double value that can be generated
	double random_double(void)
	{
		std::uniform_real_distribution<double> distribution(min_double, max_double);
		return distribution(generator);
	}


	// return random double value between given max and min double values
	double random_double(const double min_val, const double max_val)
	{
		if(min_val > max_val) throw Rand_gen_exception("Min random value cannot be greater than max random value.");

		std::uniform_real_distribution<double> distribution(min_val, max_val);
		return distribution(generator);
	}


	// return random unsigned long value between max and min unsigned long value that can be generated
	unsigned long random_unsigned_long(void)
	{
		std::uniform_int_distribution<unsigned long> distribution(min_unsigned_long, max_unsigned_long);
		return distribution(generator);
	}


	// return random unsigned long value between given max and min unsigned long values
	unsigned long random_unsigned_long(const unsigned long min_val, const unsigned long max_val)
	{
		if(min_val > max_val) throw Rand_gen_exception("Min random value cannot be greater than max random value.");

		std::uniform_int_distribution<unsigned long> distribution(min_val, max_val);
		return distribution(generator);
	}
};