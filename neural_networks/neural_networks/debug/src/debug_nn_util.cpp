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
			// test Util::clamp(unsigned long value)

			unsigned long i = random_unsigned_long();
			if(Util::clamp(i) != i) throw Neural_network_exception("Error in nn_util Util::clamp(value) function.");

			i = min_unsigned_long;
			if(Util::clamp(i) != min_unsigned_long) throw Neural_network_exception("Error in nn_util Util::clamp(value) function.");

			i = max_unsigned_long + random_unsigned_long();
			if(Util::clamp(i) != max_unsigned_long) throw Neural_network_exception("Error in nn_util Util::clamp(value) function.");

			// test Util::clamp(double value)

			double d = random_double();
			if(Util::clamp(d) != d) throw Neural_network_exception("Error in nn_util Util::clamp(value) function.");

			d = min_double - abs(random_double());
			if(Util::clamp(d) != min_double) throw Neural_network_exception("Error in nn_util Util::clamp(value) function.");

			d = max_double + abs(random_double());
			if(Util::clamp(d) != max_double) throw Neural_network_exception("Error in nn_util Util::clamp(value) function.");


			// test Util::wrap(unsigned long value)

			unsigned long i_min = random_unsigned_long();
			unsigned long i_max = i_min + random_unsigned_long();
			i = random_unsigned_long(i_min, i_max);

			if(Util::wrap(i + (i_max - i_min) * random_unsigned_long(), i_min, i_max) != i)
				throw Neural_network_exception("Error in nn_util Util::wrap(value) function.");

			try
			{
				// this must throw an exception
				Util::wrap(i, i_max, i_min);
			}
			catch(...)
			{
				goto hereI;
			}
			throw Neural_network_exception("Error in nn_util Util::wrap(value) function.");

hereI:		if(Util::wrap(i, i, i) != i) throw Neural_network_exception("Error in nn_util Util::wrap(value) function.");

			// test Util::wrap(double value)

			double d_min = random_double();
			double d_max = d_min + abs(random_double());
			d = random_double(d_min, d_max);

			if(abs(Util::wrap(d + (d_max - d_min) * (double)random_unsigned_long(), d_min, d_max) - d) > 1.0e-10)
				throw Neural_network_exception("Error in nn_util Util::wrap(value) function.");

			try
			{
				// this must throw an exception
				Util::wrap(d, d_max, d_min);
			}
			catch(...)
			{
				goto hereD;
			}
			throw Neural_network_exception("Error in nn_util Util::wrap(value) function.");

hereD:		if(Util::wrap(d, d, d) != d) throw Neural_network_exception("Error in nn_util Util::wrap(value) function.");
		}
	};
};