#include "debug_nn_util.h"
#include "nn_util.h"
#include "neural_network_exception.h"
#include "rand_gen.h"
#include "constants.h"
#include <cmath>


namespace Neural_networks
{
	namespace Debug
	{
		// debug all functions in nn_util.h
		void debug_nn_util(void)
		{
			// test clamp(unsigned long value)

			unsigned long i = random_unsigned_long();
			if(clamp(i) != i) throw Neural_network_exception("Error in nn_util clamp(value) function.");

			i = min_unsigned_long;
			if(clamp(i) != min_unsigned_long) throw Neural_network_exception("Error in nn_util clamp(value) function.");

			i = max_unsigned_long + random_unsigned_long();
			if(clamp(i) != max_unsigned_long) throw Neural_network_exception("Error in nn_util clamp(value) function.");

			// test clamp(double value)

			double d = random_double();
			if(clamp(d) != d) throw Neural_network_exception("Error in nn_util clamp(value) function.");

			d = min_double - abs(random_double());
			if(clamp(d) != min_double) throw Neural_network_exception("Error in nn_util clamp(value) function.");

			d = max_double + abs(random_double());
			if(clamp(d) != max_double) throw Neural_network_exception("Error in nn_util clamp(value) function.");
		}
	};
};