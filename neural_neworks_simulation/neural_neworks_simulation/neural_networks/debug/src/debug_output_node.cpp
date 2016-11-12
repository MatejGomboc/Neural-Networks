#include "debug_output_node.h"
#include "output_node.h"

namespace neural_networks
{
	namespace debug
	{
		void debug_output_node(void)
		{
			const unsigned long N_neurons = 100;

			Output_node test_output_node(N_neurons);

			debug_output_node(N_neurons, test_output_node);
		}

		void debug_output_node(const unsigned long N_neurons, const Output_node &test_output_node)
		{
			if(test_output_node.m_vdWeights.size() != N_neurons) throw "Invalid number of weights in output node.";

			for (unsigned long i = 0; i < test_output_node.m_vdWeights.size(); i++)
			{
				if((test_output_node.m_vdWeights[i] > 1.0) || (test_output_node.m_vdWeights[i] < 0.0)) throw "Invalid value of output node's weight.";
			}
		}
	};
};