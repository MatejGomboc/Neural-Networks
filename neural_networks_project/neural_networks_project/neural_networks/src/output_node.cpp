#include "output_node.h"
#include "neuron.h"
#include "rand_gen.h"
#include "constants.h"
#include "srestricted.h"
#include <vector>


namespace neural_networks
{
	Output_node::Output_node(const unsigned long N_neurons)
	{
		if (N_neurons <= 0) throw "Zero neurons connected to output node.";

		m_vdWeights.reserve(N_neurons);

		for (unsigned long i = 0; i != N_neurons; i++)
		{
			m_vdWeights.push_back(restricted_range::srestricted<double, 0 ,1>(random_double(0.0, 1.0)));
		}
	}


	Output_node::~Output_node(void)
	{
		m_vdWeights.clear();
	}


	 // calculate new output value from outputs of Neurons
	double Output_node::calculate(const std::vector<Neuron> &neurons) const
	{
		if(neurons.size() != m_vdWeights.size()) throw "Number of inputs from neurons' outputs does not match the number of weights in output node.";

		double summ = 0.0; // (0.0 - N_neurons)

		for(unsigned long i = 0; i != neurons.size(); i++)
		{
			summ += neurons[i].m_dOutput * m_vdWeights[i];
		}

		return (summ / static_cast<double>(neurons.size()));
	}
};