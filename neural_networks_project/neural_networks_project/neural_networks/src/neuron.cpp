#include "neuron.h"
#include "rand_gen.h"
#include <vector>
#include <math.h>


neural_networks::neuron::neuron(std::vector<double>::size_type N_weights)
{
	// N_weights = N_neurons + N_inputs

	if (N_weights <= 0) throw "Zero weights in this neuron.";

	rand_gen Rand_gen;

	output = Rand_gen.random_double(0.0, 1.0);
	temp = Rand_gen.random_double(0.0, 1.0);

	treshold = Rand_gen.random_double(0.0, (double)N_weights);
	steepness = Rand_gen.random_double();
	simetricity = Rand_gen.random_double(0.0, 1.0);

	weights.reserve(N_weights);

	for (std::vector<double>::size_type i = 0; i != N_weights; i++)
	{
		weights.push_back(Rand_gen.random_double(0.0, 1.0));
	}
}


neural_networks::neuron::~neuron(void)
{
	weights.clear();
}


void neural_networks::neuron::calculate(std::vector<neuron> neurons, std::vector<double> inputs)
{
	double summ = 0.0;
	unsigned j = 0;

	for(std::vector<double>::size_type i = 0; i != inputs.size(); i++)
	{
		summ += inputs[i] * weights[j];
		j++;
	}

	for(std::vector<neuron>::size_type i = 0; i != neurons.size(); i++)
	{
		summ += neurons[i].output * weights[j];
		j++;
	}

	temp = activation_function(summ);
}


void neural_networks::neuron::propagate(void)
{
	output = temp;
}


double neural_networks::neuron::activation_function(double summ)
{
	return (1.0 / pow((1.0 + exp(-steepness*(summ - treshold))), simetricity));
}