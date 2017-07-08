#include "neuron.h"
#include "rand_gen.h"
#include "constants.h"

#include <vector>
#include <cmath>

namespace Neural_networks
{
	Neuron::Neuron(const unsigned long N_inputs) :
		m_dTemp(outputMinValue),
		m_dOutput(outputMinValue),
		m_dTreshold(tresholdMinValue),
		m_dSteepness(random_double()),
		m_dSimetricity(random_double(simetricityMinValue, simetricityMaxValue))
	{
		// N_weights = N_inputs

		if (N_inputs <= 0) throw Neuron_exception("Cannot create a neuron with zero inputs.");

		m_dTreshold = random_double(tresholdMinValue, static_cast<double>(N_inputs));

		m_vdWeights.reserve(N_inputs);

		for (unsigned long i = 0; i < N_inputs; i++)
		{
			m_vdWeights.push_back(random_double(weightMinValue, weightMaxValue));
		}
	}


	Neuron::~Neuron(void)
	{
		m_vdWeights.clear();
	}


	double Neuron::get_output(void) const
	{
		return m_dOutput;
	}


	// get length of vector of weights
	unsigned long Neuron::get_weights_length(void) const
	{
		return m_vdWeights.size();
	}


	// get value of neuron's weight
	double Neuron::get_weight(const unsigned long indx) const
	{
		if(indx >= m_vdWeights.size()) throw Neuron_exception("Neuron weight index out of range.");

		return m_vdWeights[indx];
	}


	// set new weights
	void Neuron::set_weight(const double new_weight, const unsigned long indx)
	{
		if((new_weight < weightMinValue) || (new_weight > weightMaxValue)) throw Neuron_exception("New neuron's weight has invalid value.");
		if(indx >= m_vdWeights.size()) throw Neuron_exception("Neuron weight index out of range.");

		m_vdWeights[indx] = new_weight;
	}


	double Neuron::get_treshold(void) const
	{
		return m_dTreshold;
	}


	void Neuron::set_treshold(const double new_treshold)
	{
		if ((new_treshold < tresholdMinValue) || (new_treshold > static_cast<double>(m_vdWeights.size()))) throw Neuron_exception("New neuron's treshold has invalid value.");
		
		m_dTreshold = new_treshold;
	}


	double Neuron::get_steepness(void) const
	{
		return m_dSteepness;
	}


	void Neuron::set_steepness(const double new_steepness)
	{
		if ((new_steepness < steepnessMinValue) || (new_steepness > steepnessMaxValue)) throw Neuron_exception("New neuron's steepness has invalid value.");
		
		m_dSteepness = new_steepness;
	}


	double Neuron::get_simetricity(void) const
	{
		return m_dSimetricity;
	}


	void Neuron::set_simetricity(const double new_simetricity)
	{
		if ((new_simetricity < simetricityMinValue) || (new_simetricity > simetricityMaxValue)) throw Neuron_exception("New neuron's simetricity has invalid value.");
		
		m_dSimetricity = new_simetricity;
	}


	// calculate new output value and place it in temporal storage
	void Neuron::calculate(const std::vector<double>& inputs)
	{
		if(inputs.size() != m_vdWeights.size()) throw Neuron_exception("Invalid number of inputs to this neuron.");

		double summ = 0.0; // (0.0 - N_inputs)

		for(unsigned long i = 0; i < inputs.size(); i++)
		{
			summ += inputs[i] * m_vdWeights[i];
		}

		m_dTemp = activationFunction(summ, m_dSteepness, m_dTreshold, m_dSimetricity);
	}


	//reset neuron's output and temp_output
	void Neuron::reset(void)
	{
		m_dTemp = outputMinValue;
		m_dOutput = outputMinValue;
	}


	// place temporal storage of output value into current output value
	void Neuron::propagate(void)
	{
		m_dOutput = m_dTemp;
	}


	// neuron's activation function
	double Neuron::activationFunction(const double summ, const double steepness, const double treshold, const double simetricity)
	{
		return (1.0 / pow((1.0 + exp(-steepness*(summ - treshold))), simetricity));
	}
};