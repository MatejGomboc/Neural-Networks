#include "nn_util.h"
#include "constants.h"
#include <cmath>
#include "neural_network_exception.h"

namespace Neural_networks
{
	namespace Util
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
		double wrap (double value, const double min, const double max)
		{
			if(min > max) throw Neural_network_exception("Min value of wrap function must be smaler than max value.");

			while((value >= max) || (value < min))
			{
				if(value >= max)
				{
					if(min == max) return value;
					value -= max - min;
				}
				else if(value < min)
				{
					value += max - min;
				}
			}

			return value;
		}

		// wrap the value around the limits
		unsigned long wrap (unsigned long value, const unsigned long min, const unsigned long max)
		{
			if(min > max) throw Neural_network_exception("Min value of wrap function must be smaler than max value.");

			while((value >= max) || (value < min))
			{
				if(value >= max)
				{
					if(min == max) return value;
					value -= max - min;
				}
				else if(value < min)
				{
					value += max - min;
				}
			}

			return value;
		}
	};
};