#pragma once

#include "neuron.h"
#include "output_node.h"
#include <vector>
#include "srestricted.h"


namespace neural_networks
{
	class Network
	{
	public:
		std::vector<restricted_range::srestricted<double, 0, 1>> m_dInputs; // array of neural network inputs (0.0 - 1.0)
		std::vector<restricted_range::srestricted<double, 0, 1>> m_dOutputs; // array of neural network outputs (0.0 - 1.0)
		std::vector<Neuron> m_neurons; // array of neurons
		std::vector<Output_node> m_output_nodes; // array of output nodes
	public:
		Network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs);
		~Network(void);
		void calculate(void); // calculate new output values from current input values
	};
};