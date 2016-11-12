#pragma once

#include "output_node.h"

namespace neural_networks
{
	namespace debug
	{
		extern void debug_output_node(const unsigned long N_neurons, const Output_node &test_output_node);
		extern void debug_output_node(void);
	}
};