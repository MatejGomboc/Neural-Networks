#pragma once

#include "neural_network_exception.h"
#include <vector>


namespace Neural_networks
{
	class Output_node_exception: public Neural_network_exception
	{
	public:
		explicit Output_node_exception(const std::string message)
			: Neural_network_exception(message)
		{
		}
	};


	class Output_node
	{
	private:
		std::vector<double> m_vdWeights; // array of weights (0.0 - 1.0), N_weights = N_inputs
	public:
		explicit Output_node(const unsigned long N_inputs);
		~Output_node(void);

		unsigned long get_weights_length(void) const; // get length of vector of weights
		double get_weight(const unsigned long indx) const; // get value of output nodes's weight
		void set_weight(const double new_weight, const unsigned long indx); // set new weight's value

		double calculate(const std::vector<double>& inputs) const; // calculate new output value from inputs
	};
};

