#include "util.h"
#include "constants.h"

namespace neural_networks
{
	// restrict input double value between max and min random double value that can be generated
	double clamp_value(const double value)
	{
		if (value >= max_double) return max_double;
		else if (value <= min_double) return min_double;
		else return value;
	}

	// restrict input int value between max and min random int value that can be generated
	int clamp_value(const int value)
	{
		if (value >= max_int) return max_int;
		else if (value <= min_int) return min_int;
		else return value;
	}
};