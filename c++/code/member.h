#pragma once

#include "network.h"
#include "member.h"
#include "output_node.h"
#include "neuron.h"
#include <vector>


namespace neural_networks
{
	class member
	{
	public:
		double fitness; // fitness value (0.0 - 1.0)
		network brain; // neural network, "the brain" of population member
	public:
		member(std::vector<double>::size_type N_inputs, std::vector<neuron>::size_type N_neurons, std::vector<output_node>::size_type N_outputs);
		~member(void);
	};
};