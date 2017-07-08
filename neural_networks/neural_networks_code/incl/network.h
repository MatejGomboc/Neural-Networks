#pragma once

#include "neuron.h"
#include "output_node.h"
#include "neural_network_exception.h"

#include <vector>


namespace Neural_networks
{
	class Network_exception: public Neural_network_exception
	{
	public:
		explicit Network_exception(const std::string message)
			: Neural_network_exception(message)
		{
		}
	};


	class Network
	{
	private:
		std::vector<double> m_dInputs; // array of neural network inputs (0.0 - 1.0)
		std::vector<double> m_dOutputs; // array of neural network outputs (0.0 - 1.0)
		std::vector<Neuron> m_neurons; // array of neurons
		std::vector<Output_node> m_output_nodes; // array of output nodes
	public:
		Network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs);
		~Network(void);

		unsigned long get_num_inputs(void) const;
		void set_input(const double new_input, const unsigned long indx);

		unsigned long get_num_outputs(void) const;
		double get_output(const unsigned long indx) const;

		unsigned long get_num_neurons(void) const;
		unsigned long get_neuron_weights_length(const unsigned long neuron_indx) const;
		double get_neuron_weight(const unsigned long neuron_indx, const unsigned long weight_indx) const;
		void set_neuron_weight(const double new_weight, const unsigned long neuron_indx, const unsigned long weight_indx);
		double get_neuron_treshold(const unsigned long neuron_indx) const;
		void set_neuron_treshold(const double new_treshold, const unsigned long neuron_indx);
		double get_neuron_steepness(const unsigned long neuron_indx) const;
		void set_neuron_steepness(const double new_steepness, const unsigned long neuron_indx);
		double get_neuron_simetricity(const unsigned long neuron_indx) const;
		void set_neuron_simetricity(const double new_simetricity, const unsigned long neuron_indx);

		unsigned long get_num_output_nodes(void) const;
		unsigned long get_output_node_weights_length(const unsigned long output_node_indx) const;
		double get_output_node_weight(const unsigned long output_node_indx, const unsigned long weight_indx) const;
		void set_output_node_weight(const double new_weight, const unsigned long output_node_indx, const unsigned long weight_indx);

		void calculate(void); // calculate new output values from current input values
		void reset(void); // reset inputs, outputs and neuron outputs and temp_outputs
	};
};