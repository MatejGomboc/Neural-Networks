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
			const unsigned long N_weights = 100;

			Neuron test_neuron(N_weights);

			debug_neuron(N_weights, test_neuron);
		}

		void debug_neuron(const unsigned long N_weights, const Neuron &test_neuron)
		{
			if(test_neuron.m_vdWeights.size() != N_weights) throw "Invalid number of weights in neuron.";

			if(test_neuron.m_dTreshold > static_cast<double>(test_neuron.m_vdWeights.size())) throw "Invalid value of neuron's treshold value.";

			for (unsigned long i = 0; i < test_neuron.m_vdWeights.size(); i++)
			{
				if((test_neuron.m_vdWeights[i] > 1.0) || (test_neuron.m_vdWeights[i] < 0.0)) throw "Invalid value of neuron's weight.";
			}
		}
	};
};