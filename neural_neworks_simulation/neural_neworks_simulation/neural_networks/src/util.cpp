#include "util.h"
#include "constants.h"
#include <cmath>

namespace neural_networks
{
	// restrict input double value between max and min random double value that can be generated
	double clamp(const double value)
	{
		if (value >= max_double) return max_double;
		else if (value <= min_double) return min_double;
		else return value;
	}

	// restrict input int value between max and min random int value that can be generated
	int clamp(const int value)
	{
		if (value >= max_int) return max_int;
		else if (value <= min_int) return min_int;
		else return value;
	}

	// wrap the value around the limits
	double wrap (const double value, const double min, const double max)
	{
		return(value - (max - min) * floor(value / (max - min)));
	}

	// wrap the value around the limits
	int wrap (const int value, const int min, const int max)
	{
		if (value < min)
			return(max - (min - value) % (max - min));
		else
			return(min + (value - min) % (max - min));
	}
};