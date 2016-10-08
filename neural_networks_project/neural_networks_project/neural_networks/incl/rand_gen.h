#pragma once

#include <random>

namespace neural_networks
{
	extern double random_double(void); // return random double value between max and min double value that can be generated
	extern double random_double(const double min_val, const double max_val); // return random double value between given max and min double values
	extern int random_int(void); // return random int value between max and min int value that can be generated
	extern int random_int(const int min_val, const int max_val); // return random int value between given max and min int values
};
