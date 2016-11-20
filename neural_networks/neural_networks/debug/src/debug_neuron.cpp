#include "debug_neuron.h"
#include "rand_gen.h"
#include "neuron.h"
#include "srestricted.h"
#include <vector>


namespace Neural_networks
{
	namespace Debug
	{
		static void test_constructor(void)
		{
			// test neuron's constructor for bugs
			const unsigned long N_weights = random_unsigned_long(1, 100);
			Neuron test_neuron1(N_weights);

			// test neuron for correct number of weights and corect threshold value
			test_neuron1.test(N_weights);

			// user should not be able to create a neuron with zero weights,
			// otherwise it's an error
			try
			{
				// this must throw an exception
				Neuron test_neuron2(0);
			}
			catch(...)
			{
				return;
			}
			throw Neuron_exception("Neuron with zero weights created. Check constructor.");
		}

		static void test_calculation(void)
		{
			// create test neuron
			const unsigned long N_neurons = random_unsigned_long(1, 100);
			const unsigned long N_inputs = random_unsigned_long(1, 100);
			Neuron test_neuron(N_neurons + N_inputs);
			
			// test calculation function (normal case)
			std::vector<Neuron> neurons1;
			neurons1.reserve(N_neurons);
			for (unsigned long i = 0; i < N_neurons; i++)
			{
				neurons1.push_back(Neuron(N_neurons + N_inputs));
				neurons1[i].m_dOutput = random_double(0.0, 1.0);
			}

			std::vector<Restricted_range::srestricted<double, 0, 1>> inputs1;
			inputs1.reserve(N_inputs);
			for(unsigned long i = 0; i < N_inputs; i++)
			{
				inputs1.push_back(Restricted_range::srestricted<double, 0, 1>(random_double(0.0, 1.0)));
			}

			test_neuron.calculate(neurons1, inputs1);

			// test calculation function (in case of zero inputs from neurons)
			std::vector<Neuron> neurons2;
			neurons2.clear();

			try
			{
				// this must throw an exception
				test_neuron.calculate(neurons2, inputs1);
			}
			catch(...)
			{
				goto here;
			}
			throw Neuron_exception("Zero inputs from neurons during calculation. Check calculation function.");

			// test calculation function (in case of zero NN inputs)
here:		std::vector<Restricted_range::srestricted<double, 0, 1>> inputs2;
			inputs2.clear();

			try
			{
				// this must throw an exception
				test_neuron.calculate(neurons1, inputs2);
			}
			catch(...)
			{
				return;
			}
			throw Neuron_exception("Zero NN inputs during calculation. Check calculation function.");
		}

		void debug_neuron(void)
		{
			test_constructor();
			test_calculation();
		}
	};
};