#include "output_node.h"
#include "neuron.h"
#include "rand_gen.h"
#include <vector>


neural_networks::output_node::output_node(std::vector<neuron>::size_type N_neurons)
{
	if (N_neurons <= 0) throw "Zero neurons connected to output node.";

	rand_gen Rand_gen;

	weights.reserve(N_neurons);

	for (std::vector<neuron>::size_type i = 0; i != N_neurons; i++)
	{
		weights.push_back(Rand_gen.random_double(0.0, 1.0));
	}
}


neural_networks::output_node::~output_node(void)
{
	weights.clear();
}


double neural_networks::output_node::calculate(std::vector<neuron> neurons)
{
	double summ = 0.0; // (0.0 - N_neurons)

	for(std::vector<neuron>::size_type i = 0; i != neurons.size(); i++)
	{
		summ += neurons[i].output * weights[i];
	}

	return (summ / (double)neurons.size());
}