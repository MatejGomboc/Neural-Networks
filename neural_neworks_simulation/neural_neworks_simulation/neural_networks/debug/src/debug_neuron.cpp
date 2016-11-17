#include "debug_neuron.h"
#include "constants.h"
#include "rand_gen.h"
#include "neuron.h"


namespace neural_networks
{
	namespace debug
	{
		void debug_neuron(void)
		{
			// test neuron's constructor for bugs

			const unsigned long N_weights = random_int(1, 100);

			Neuron test_neuron1(N_weights);

			debug_neuron(N_weights, test_neuron1);

			// test neuron's calculation function (normal case)

			Neuron test_neuron2(2);

			test_neuron2.calculate(

			// test neuron's calculation function (in case of zero neuron inputs)
			try
			{
			}
			catch(...)
			{
			}

			// test neuron's calculation function (in case of zero neural network inputs)
			try
			{
			}
			catch(...)
			{
			}

			// user should not be able to create a neuron with zero weights
			try
			{
				Neuron test_neuron3(0);
			}
			catch(...)
			{
				return;
			}

			throw Neuron_exception("Neuron with zero weights created. Check constructor.");
		}

		void debug_neuron(const unsigned long N_weights, const Neuron &test_neuron)
		{
			test_neuron.test(N_weights);
		}
	};
};