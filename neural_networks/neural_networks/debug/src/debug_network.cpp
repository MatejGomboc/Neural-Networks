#include "debug_network.h"
#include "debug_neuron.h"
#include "debug_output_node.h"
#include "rand_gen.h"
#include "neuron.h"
#include "output_node.h"
#include "network.h"
#include <vector>


namespace Neural_networks
{
	namespace Debug
	{
		static void test_constructor(void)
		{
			// test networks's constructor for bugs
			const unsigned long N_inputs = random_unsigned_long(1, 100);
			const unsigned long N_neurons = random_unsigned_long(1, 100);
			const unsigned long N_outputs = random_unsigned_long(1, 100);

			Network test_network1(N_inputs, N_neurons, N_outputs);
			debug_network(N_inputs, N_neurons, N_outputs, test_network1);

			// if zero inputs
			try
			{
				// this must throw an exception
				Network test_network2(0, N_neurons, N_outputs);
			}
			catch(...)
			{
				goto here1;
			}
			throw Network_exception("Network with zero inputs created. Check constructor.");

			// if zero neurons
here1:		try
			{
				// this must throw an exception
				Network test_network3(N_inputs, 0, N_outputs);
			}
			catch(...)
			{
				goto here2;
			}
			throw Network_exception("Network with zero neurons created. Check constructor.");

			// if zero outputs
here2:		try
			{
				// this must throw an exception
				Network test_network4(N_inputs, N_neurons, 0);
			}
			catch(...)
			{
				return;
			}
			throw Network_exception("Network with zero outputs created. Check constructor.");
		}

		static void test_calculation(void)
		{
			// test networks's calculation function
			const unsigned long N_inputs = random_unsigned_long(1, 100);
			const unsigned long N_neurons = random_unsigned_long(1, 100);
			const unsigned long N_outputs = random_unsigned_long(1, 100);

			Network test_network(N_inputs, N_neurons, N_outputs);
			debug_network(N_inputs, N_neurons, N_outputs, test_network);

			for (unsigned long i = 0; i < test_network.m_dInputs.size(); i++)
			{
				test_network.m_dInputs[i] = random_double(0.0, 1.0);
			}

			for (unsigned long i = 0; i < test_network.m_neurons.size(); i++)
			{
				test_network.m_neurons[i].m_dOutput = random_double(0.0, 1.0);
			}

			test_network.calculate();
		}

		void debug_network(void)
		{
			test_constructor();
			test_calculation();
		}


		void debug_network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Network& test_network)
		{
			test_network.test();

			if(N_inputs != test_network.m_dInputs.size()) throw Network_exception("This neural network has invalid number of inputs.");
			if(N_neurons != test_network.m_neurons.size()) throw Network_exception("This neural network has invalid number of neurons.");
			if(N_outputs != test_network.m_dOutputs.size()) throw Network_exception("This neural network has invalid number of outputs.");
		}
	};
};