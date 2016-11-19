#pragma once

#include "neuron.h"
#include <vector>
#include "srestricted.h"
#include "neural_network_exception.h"

namespace Neural_networks
{
	class Output_node_exception: public Neural_network_exception
	{
	public:
		explicit Output_node_exception(const std::string message)
			: Neural_network_exception(message)
		{
		}
	};


	class Output_node
	{
	public:
		std::vector<Restricted_range::srestricted<double, 0, 1>> m_vdWeights; // array of weights (0.0 - 1.0), N_weights = N_neurons
	public:
		explicit Output_node(const unsigned long N_neurons);
		~Output_node(void);
		double calculate(const std::vector<Neuron>& neurons) const; // calculate new output value from outputs of neurons
		void test(const unsigned long N_neurons) const; // test output node for valid number of weights
	};
};

