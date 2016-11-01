#include "debug_network.h"
#include "debug_neuron.h"
#include "debug_output_node.h"
#include "constants.h"
#include "rand_gen.h"
#include "neuron.h"
#include "output_node.h"
#include "network.h"
#include <vector>


namespace neural_networks
{
	namespace debug
	{
		void debug_network(void)
		{
			const unsigned long N_inputs = 10;
			const unsigned long N_neurons = 100;
			const unsigned long N_outputs = 5;

			Network test_network(N_inputs, N_neurons, N_outputs);

			debug_network(N_inputs, N_neurons, N_outputs, test_network);
		}


		void debug_network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Network& test_network)
		{
			static int indx_run = 0;

			if(test_network.m_dInputs.size() != N_inputs) throw "Invalid number of inputs in network.";
			if(test_network.m_dOutputs.size() != N_outputs) throw "Invalid number of outputs in network.";
			if(test_network.m_neurons.size() != N_neurons) throw "Invalid number of neurons in network.";
			if(test_network.m_output_nodes.size() != N_outputs) throw "Invalid number of output nodes in network.";

			// generate random values of inputs of network
			for(unsigned long i = 0; i < test_network.m_dInputs.size(); i++)
			{
				test_network.m_dInputs[i] = random_double(0.0, 1.0);
			}

			for(unsigned long i = 0; i < test_network.m_neurons.size(); i++)
			{
				debug_neuron(N_inputs + N_neurons, test_network.m_neurons[i]);
			}

			for(unsigned long i = 0; i < test_network.m_output_nodes.size(); i++)
			{
				debug_output_node(N_neurons, test_network.m_output_nodes[i]);
			}

			for(unsigned long i = 0; i < test_network.m_dOutputs.size(); i++)
			{
				if((test_network.m_dOutputs[i] < 0.0) || (test_network.m_dOutputs[i] > 1.0)) throw "Invalid value of network's output.";
			}

			if(indx_run == 1) return;
			test_network.calculate();
			indx_run++;
			debug_network(N_inputs, N_neurons, N_outputs, test_network);
		}
	};
};