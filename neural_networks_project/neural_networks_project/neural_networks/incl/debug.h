#pragma once

#include "neuron.h"
#include "output_node.h"
#include "network.h"
#include "member.h"
#include "population.h"

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
		extern void debug_network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Network& test_network);
		extern void debug_network(void);
		extern void debug_member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Member& test_member);
		extern void debug_member(void);
		extern void debug_population(const unsigned long N_members, const unsigned long N_memb_input_variables, const unsigned long N_memb_neurons, const unsigned long N_memb_output_variables, const Mutation_params& mutation_params, Population& test_population);
		extern void debug_population(void);
	}
};