#pragma once

#include <vector>

namespace neural_networks
{
	class neuron
	{
	public:
		double output; // current output value (0.0 - 1.0)
		std::vector<double> weights; // array of weights (0.0 - 1.0)
		double temp; // temporal storage of output value (0.0 - 1.0)
		double treshold; // activation function treshold (0.0 - 1.0 * (N_neurons + N_inputs))
		double steepness;  // activation function steepness (-1000.0 - 1000.0)
		double simetricity;  // activation function simetricity (0.0 - 1.0)
	public:
		neuron(std::vector<double>::size_type N_weights);
		~neuron(void);
		void propagate(void); // place temporal storage of output value into current output value
		void calculate(std::vector<neuron> neurons, std::vector<double> inputs); // calculate new output value and place it in temporal storage
	private:
		double activation_function(double summ); // neuron's activation function
	};
};