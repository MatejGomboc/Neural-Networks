#pragma once

#include "neuron.h"
#include "output_node.h"
#include "network.h"


namespace neural_networks
{
	namespace debug
	{
		extern void debug_network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Network& test_network);
		extern void debug_network(void);
	}
};