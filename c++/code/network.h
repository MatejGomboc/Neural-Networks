#pragma once

#include "neuron.h"
#include "output_node.h"
#include <vector>


namespace neural_networks
{
	class network
	{
	public:
		std::vector<double> inputs; // array of neural network inputs (0.0 - 1.0)
		std::vector<double> outputs; // array of neural network outputs (0.0 - 1.0)
		std::vector<neuron> neurons; // array of neurons
		std::vector<output_node> output_nodes; // array of output nodes
	public:
		network(std::vector<double>::size_type N_inputs, std::vector<neuron>::size_type N_neurons, std::vector<output_node>::size_type N_outputs);
		~network(void);
		void calculate(void); // calculate new output values from current input values
	};
};