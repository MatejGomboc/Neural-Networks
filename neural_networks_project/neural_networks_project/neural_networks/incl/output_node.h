#pragma once

#include "neuron.h"
#include <vector>
#include "srestricted.h"

namespace neural_networks
{
	class Output_node
	{
	public:
		std::vector<restricted_range::srestricted<double, 0, 1>> m_vdWeights; // array of weights (0.0 - 1.0), N_weights = N_neurons
	public:
		Output_node(const unsigned long N_neurons);
		~Output_node(void);
		double calculate(const std::vector<Neuron>& neurons) const; // calculate new output value from outputs of neurons
	};
};

