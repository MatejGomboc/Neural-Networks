#include "neuron.h"
#include "rand_gen.h"

#include <vector>
#include <cmath>

namespace neural_networks
{
	Neuron::Neuron(const unsigned long N_weights)
	{
		// N_weights = N_neurons + N_inputs

		if (N_weights <= 0) throw "Invalid number of weights in neuron.";

		m_dOutput = 0.0; //random_double(0.0, 1.0);
		m_dTemp = 0.0; //random_double(0.0, 1.0);

		m_dTreshold = random_double(0.0, static_cast<double>(N_weights));
		m_dSteepness = random_double();
		m_dSimetricity = random_double(0.0, 1.0);

		m_vdWeights.reserve(N_weights);

		for (unsigned long i = 0; i != N_weights; i++)
		{
			m_vdWeights.push_back(random_double(0.0, 1.0));
		}
	}


	Neuron::~Neuron(void)
	{
		m_vdWeights.clear();
	}


	 // calculate new output value and place it in temporal storage
	void Neuron::calculate(const std::vector<Neuron> &neurons, const std::vector<double> &inputs)
	{
		// N_weights = N_neurons + N_inputs
		if((neurons.size() + inputs.size()) != m_vdWeights.size()) throw "Number of inputs from network inputs and other neurons' outputs does not match the number of weights in neuron.";

		double summ = 0.0;  // (0.0 - (N_neurons + N_inputs))
		unsigned long j = 0;

		for(unsigned long i = 0; i != inputs.size(); i++)
		{
			summ += inputs[i] * m_vdWeights[j];
			j++;
		}

		for(unsigned long i = 0; i != neurons.size(); i++)
		{
			summ += neurons[i].m_dOutput * m_vdWeights[j];
			j++;
		}

		m_dTemp = activation_function(summ, m_dSteepness, m_dTreshold, m_dSimetricity);
	}


	// place temporal storage of output value into current output value
	void Neuron::propagate(void)
	{
		m_dOutput = m_dTemp;
	}


	// neuron's activation function
	double Neuron::activation_function(const double summ, const double steepness, const double treshold, const double simetricity)
	{
		return (1.0 / pow((1.0 + exp(-steepness*(summ - treshold))), simetricity));
	}
};