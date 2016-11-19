#pragma once

#include <random>
#include "neural_network_exception.h"

namespace Neural_networks
{
	class Rand_gen_exception: public Neural_network_exception
	{
	public:
		explicit Rand_gen_exception(const std::string message)
			: Neural_network_exception(message)
		{
		}
	};

	extern double random_double(void); // return random double value between max and min double value that can be generated
	extern double random_double(const double min_val, const double max_val); // return random double value between given max and min double values
	extern unsigned long random_unsigned_long(void); // return random unsigned long value between max and min unsigned long value that can be generated
	extern unsigned long random_unsigned_long(const unsigned long min_val, const unsigned long max_val); // return random unsigned long value between given max and min unsigned long values
};
