#pragma once

#include "neuron.h"
#include <vector>
#include "restricted.h"
#include "IRestrictedRange.h"

namespace neural_networks
{
	class Output_node : private IRestrictedRange<double>
	{
	public:
		std::vector<restricted<double>> m_vdWeights;// array of weights (0.0 - 1.0), N_weights = N_neurons
	public:
		Output_node(const unsigned long N_neurons);
		~Output_node(void);
		double calculate(const std::vector<Neuron>& neurons) const; // calculate new output value from outputs of neurons
	};
};

