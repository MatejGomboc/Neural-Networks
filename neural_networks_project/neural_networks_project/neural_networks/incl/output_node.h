#pragma once

#include "neuron.h"
#include <vector>

namespace neural_networks
{
	class output_node
	{
	public:
		std::vector<double> weights; // array of weights (0.0 - 1.0)
	public:
		output_node(std::vector<neuron>::size_type N_neurons);
		~output_node(void);
		double calculate(std::vector<neuron> neurons); // calculate output value from output values of neurons
	};
};

