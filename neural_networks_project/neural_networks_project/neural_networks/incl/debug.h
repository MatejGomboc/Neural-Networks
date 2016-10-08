#pragma once

#include "neuron.h"
#include "output_node.h"

#include <string>

namespace neural_networks
{
	namespace debug
	{
		extern void debug_rand_gen_double(const std::string file_name);
		extern void debug_rand_gen_int(const std::string file_name);
		extern void debug_neuron(const unsigned long N_weights, const Neuron &test_neuron);
		extern void debug_neuron(void);
		extern void debug_output_node(const unsigned long N_neurons, const Output_node &test_output_node);
		extern void debug_output_node(void);
		extern void debug_network(void);
	}
};