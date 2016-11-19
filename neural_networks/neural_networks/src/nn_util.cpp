#include "nn_util.h"
#include "constants.h"
#include <cmath>

namespace Neural_networks
{
	// restrict input double value between max and min random double value that can be generated
	double clamp(const double value)
	{
		if (value >= max_double) return max_double;
		else if (value <= min_double) return min_double;
		else return value;
	}

	// restrict input unsigned long value between max and min random unsigned long value that can be generated
	unsigned long clamp(const unsigned long value)
	{
		if (value >= max_unsigned_long) return max_unsigned_long;
		else if (value <= min_unsigned_long) return min_unsigned_long;
		else return value;
	}

	// wrap the value around the limits
	double wrap (const double value, const double min, const double max)
	{
		return(value - (max - min) * floor(value / (max - min)));
	}

	// wrap the value around the limits
	unsigned long wrap (const unsigned long value, const unsigned long min, const unsigned long max)
	{
		if (value < min)
			return(max - (min - value) % (max - min));
		else
			return(min + (value - min) % (max - min));
	}
};