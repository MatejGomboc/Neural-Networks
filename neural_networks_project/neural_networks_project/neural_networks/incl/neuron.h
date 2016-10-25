#pragma once

#include <vector>
#include "restricted.h"
#include "IRestrictedRange.h"


namespace neural_networks
{
	class Neuron : private IRestrictedRange<double>
	{
	public:
		restricted<double> m_dOutput; // current output value (0.0 - 1.0)
		std::vector<restricted<double>> m_vdWeights; // array of weights (0.0 - 1.0), N_weights = N_neurons + N_inputs
		restricted<double> m_dTemp; // temporal storage of output value (0.0 - 1.0)
		restricted<double> m_dTreshold; // activation function treshold (0.0 - N_weights)
		restricted<double> m_dSteepness; // activation function steepness (-1000.0 - 1000.0)
		restricted<double> m_dSimetricity; // activation function simetricity (0.0 - 1.0)
	public:
		Neuron(const unsigned long N_weights);
		~Neuron(void);
		void propagate(void); // place temporal storage of output value into current output value
		void calculate(const std::vector<Neuron>& neurons, const std::vector<restricted<double>>& inputs); // calculate new output value and place it in temporal storage
		static double activation_function(const double summ, const double steepness, const double treshold, const double simetricity); // neuron's activation function
	};
};