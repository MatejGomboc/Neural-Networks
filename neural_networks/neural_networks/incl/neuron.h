#pragma once

#include <vector>
#include <string>
#include "restricted.h"
#include "srestricted.h"
#include "neural_network_exception.h"
#include "tinyxml2.h"


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
		Restricted_range::srestricted<double, 0, 1> m_dTemp; // temporal storage of output value (0.0 - 1.0)
	public:
		Restricted_range::srestricted<double, 0, 1> m_dOutput; // current output value (0.0 - 1.0)

		// array of weights (0.0 - 1.0), N_weights = N_neurons + N_inputs
		std::vector<Restricted_range::srestricted<double, 0, 1>> m_vdWeights;

		Restricted_range::restricted<double> m_dTreshold; // activation function treshold (0.0 - N_weights)
		Restricted_range::srestricted<double, -1000, 1000> m_dSteepness; // activation function steepness (-1000.0 - 1000.0)
		Restricted_range::srestricted<double, 0, 1> m_dSimetricity; // activation function simetricity (0.0 - 1.0)
	public:
		explicit Neuron(const unsigned long N_weights);
		~Neuron(void);
		void propagate(void); // place temporal storage of output value into current output value

		// calculate new output value and place it in temporal storage
		void calculate(const std::vector<Neuron>& neurons, const std::vector<Restricted_range::srestricted<double, 0, 1>>& inputs);

		void reset(void); // reset neuron's output and temp_output
		void test(const unsigned long N_weights) const; // test neuron for correct number of weights and corect threshold value

		static Neuron XML_deserialize(tinyxml2::XMLElement* xml_element);
	private:
		// neuron's activation function
		static double activation_function(const double summ, const double steepness, const double treshold, const double simetricity);
	};
};