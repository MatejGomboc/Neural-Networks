#pragma once

#include "neural_network_exception.h"
#include <vector>


namespace Neural_networks
{
	class Neuron_exception: public Neural_network_exception
	{
	public:
		explicit Neuron_exception(const std::string message)
			: Neural_network_exception(message)
		{
		}
	};


	class Neuron
	{
	private:
		double m_dTemp; // temporal storage of output value (0.0 - 1.0)
		double m_dOutput; // current output value (0.0 - 1.0)

		std::vector<double> m_vdWeights; // array of weights (0.0 - 1.0), N_weights = N_neurons + N_inputs

		double m_dTreshold; // activation function treshold (0.0 - N_weights)
		double m_dSteepness; // activation function steepness (-1000.0 - 1000.0)
		double m_dSimetricity; // activation function simetricity (0.0 - 1.0)

	public:
		explicit Neuron(const unsigned long N_inputs);
		~Neuron(void);

		double get_output(void) const;

		unsigned long get_weights_length(void) const; // get length of vector of weights
		double get_weight(const unsigned long indx) const; // get value of neuron's weight
		void set_weight(const double new_weight, const unsigned long indx); // set new weight's value

		double get_treshold(void) const;
		void set_treshold(const double new_treshold);

		double get_steepness(void) const;
		void set_steepness(const double new_steepness);

		double get_simetricity(void) const;
		void set_simetricity(const double new_simetricity);

		void propagate(void); // place temporal storage of output value into current output value
		void calculate(const std::vector<double>& inputs); // calculate new output value and place it in temporal storage
		void reset(void); // reset neuron's output and temp_output

	private:
		static double activationFunction(const double summ, const double steepness, const double treshold, const double simetricity); // neuron's activation function
	};
};