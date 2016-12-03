#include "neuron.h"
#include "rand_gen.h"
#include "constants.h"
#include "srestricted.h"
#include "restricted.h"

#include <vector>
#include <cmath>

namespace Neural_networks
{
	Neuron::Neuron(const unsigned long N_weights) :
		m_dOutput(0.0), 
		m_dTemp(0.0),
		m_dTreshold(tresholdMinValue, tresholdMinValue),
		m_dSteepness(random_double()),
		m_dSimetricity(random_double(0.0, 1.0))
	{
		// N_weights = N_neurons + N_inputs

		if (N_weights <= 0) throw Neuron_exception("Cannot create a neuron with zero weights.");

		//m_dOutput = random_double(0.0, 1.0); //TODO!!!
		//m_dTemp = random_double(0.0, 1.0); //TODO!!

		Restricted_range::restricted_setMax(static_cast<double>(N_weights), m_dTreshold);

		m_dTreshold = random_double(0.0, static_cast<double>(N_weights));

		m_vdWeights.reserve(N_weights);

		for (unsigned long i = 0; i < N_weights; i++)
		{
			m_vdWeights.push_back(Restricted_range::srestricted<double, 0, 1>(random_double(0.0, 1.0)));
		}
	}


	Neuron::~Neuron(void)
	{
		//m_vdWeights.clear();
	}


	 // calculate new output value and place it in temporal storage
	void Neuron::calculate(const std::vector<Neuron>& neurons, const std::vector<Restricted_range::srestricted<double, 0, 1>>& inputs)
	{
		if(neurons.size() == 0)
			throw Neuron_exception("Zero inputs from other neurons to this neuron.");
		if(inputs.size() == 0)
			throw Neuron_exception("Zero inputs from neural network inputs to this neuron.");

		// N_weights = N_neurons + N_inputs
		test(neurons.size() + inputs.size());

		double summ = 0.0; // (0.0 - (N_neurons + N_inputs))
		unsigned long j = 0;

		for(unsigned long i = 0; i < inputs.size(); i++)
		{
			summ += inputs[i] * m_vdWeights[j];
			j++;
		}

		for(unsigned long i = 0; i < neurons.size(); i++)
		{
			summ += neurons[i].m_dOutput * m_vdWeights[j];
			j++;
		}

		m_dTemp = activation_function(summ, m_dSteepness, m_dTreshold, m_dSimetricity);
	}


	//reset neuron's output and temp_output
	void Neuron::reset(void)
	{
		m_dTemp = 0.0;
		m_dOutput = 0.0;
	}


	//test neuron for correct number of weights and corect threshold value
	void Neuron::test(const unsigned long N_weights) const
	{
		if(m_vdWeights.size() == 0)
			throw Neuron_exception("This neuron has zero weights.");

		// N_weights = N_neurons + N_inputs
		if(N_weights != m_vdWeights.size())
			throw Neuron_exception("Invalid number of weights in this neuron.");

		if(m_dTreshold < 0.0) throw "Neuron's treshold value is lower than 0.";
		if(m_dTreshold > static_cast<double>(m_vdWeights.size())) throw "Neuron's treshold value is greater than the number of weights in this neuron.";
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