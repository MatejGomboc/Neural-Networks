#include "debug_output_node.h"
#include "output_node.h"
#include "rand_gen.h"
#include <vector>

namespace Neural_networks
{
	namespace Debug
	{
		static void test_constructor(void)
		{
			// test output node's constructor for bugs
			const unsigned long N_neurons = random_unsigned_long(1, 100);
			Output_node test_output_node1(N_neurons);
			debug_output_node(N_neurons, test_output_node1);

			// user should not be able to create an output node with zero weights,
			// otherwise it's an error
			try
			{
				// this must throw an exception
				Output_node test_output_node2(0);
			}
			catch(...)
			{
				return;
			}
			throw Output_node_exception("Output node with zero weights created. Check constructor.");
		}

		static void test_calculation(void)
		{
			// create test output node
			const unsigned long N_neurons = random_unsigned_long(1, 100);
			Output_node test_output_node(N_neurons);
			
			// test calculation function (normal case)
			std::vector<Neuron> neurons1;
			neurons1.reserve(N_neurons);
			for (unsigned long i = 0; i < N_neurons; i++)
			{
				neurons1.push_back(Neuron(1));
				neurons1[i].m_dOutput = random_double(0.0, 1.0);
			}

			test_output_node.calculate(neurons1);

			// test calculation function (in case of zero outputs from neurons)
			std::vector<Neuron> neurons2;
			neurons2.clear();

			try
			{
				// this must throw an exception
				test_output_node.calculate(neurons2);
			}
			catch(...)
			{
				return;
			}
			throw Neuron_exception("Zero outputs from neurons during calculation. Check calculation function.");
		}

		void debug_output_node(void)
		{
			test_constructor();
			test_calculation();
		}

		void debug_output_node(const unsigned long N_neurons, const Output_node &test_output_node)
		{
			test_output_node.test(N_neurons);
		}
	};
};