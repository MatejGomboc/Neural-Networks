#include "network.h"
#include "neuron.h"
#include "output_node.h"


neural_networks::network::network(std::vector<double>::size_type N_inputs, std::vector<neuron>::size_type N_neurons, std::vector<output_node>::size_type N_outputs)
{
	if (N_inputs <= 0) throw "Zero neural network inputs.";
	if (N_outputs <= 0) throw "Zero neural network outputs.";
	if (N_neurons <= 0) throw "Zero neurons in neural network.";

	inputs.resize(N_inputs);
	outputs.resize((std::vector<double>::size_type)N_outputs);

	neurons.reserve(N_neurons);

	for (std::vector<neuron>::size_type i = 0; i != N_neurons; i++)
	{
		neurons.push_back(neuron(N_neurons+N_inputs));
	}

	output_nodes.reserve(N_outputs);

	for (std::vector<output_node>::size_type i = 0; i != N_outputs; i++)
	{
		output_nodes.push_back(output_node(N_neurons));
	}
}


neural_networks::network::~network(void)
{
	inputs.clear();
	outputs.clear();
	neurons.clear();
	output_nodes.clear();
}


void neural_networks::network::calculate(void)
{
	for(std::vector<neuron>::size_type i = 0; i != neurons.size(); i++)
	{
		neurons[i].calculate(neurons, inputs);
	}

	for(std::vector<neuron>::size_type i = 0; i != neurons.size(); i++)
	{
		neurons[i].propagate();
	}

	for(std::vector<output_node>::size_type i = 0; i != output_nodes.size(); i++)
	{
		outputs[i] = output_nodes[i].calculate(neurons);
	}
}