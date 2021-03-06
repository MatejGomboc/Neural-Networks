#pragma once

#include "constants.h"


namespace Neural_networks
{
	namespace Util
	{
		extern double clamp(const double value, const double min = min_double, const double max = max_double); // restrict input double value between max and min random double value that can be generated
		extern unsigned long clamp(const unsigned long value, const unsigned long min = min_unsigned_long, const unsigned long max = max_unsigned_long); // restrict input unsigned long value between max and min random unsigned long value that can be generated
		extern double wrap(const double value, const double min = min_double, const double max = max_double); // wrap the value around the limits
		extern unsigned long wrap(const unsigned long value, const unsigned long min = min_unsigned_long, const unsigned long max = max_unsigned_long); // wrap the value around the limits
	};
};