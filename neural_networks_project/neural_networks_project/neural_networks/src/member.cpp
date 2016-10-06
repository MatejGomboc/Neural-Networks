#include "member.h"
#include "output_node.h"
#include "neuron.h"
#include <vector>


neural_networks::member::member(std::vector<double>::size_type N_inputs, std::vector<neuron>::size_type N_neurons, std::vector<output_node>::size_type N_outputs)
	: brain(N_inputs, N_neurons, N_outputs)
{
	fitness = 0.0;
}


neural_networks::member::~member(void)
{
	brain.~network();
}