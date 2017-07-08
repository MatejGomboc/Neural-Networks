#include "network.h"
#include "neuron.h"
#include "output_node.h"
#include "constants.h"

#include <vector>


namespace Neural_networks
{
	Network::Network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs)
	{
		if (N_inputs <= 0) throw Network_exception("Cannot create neural network with zero inputs.");
		if (N_neurons <= 0) throw Network_exception("Cannot create neural network with zero neurons.");
		if (N_outputs <= 0) throw Network_exception("Cannot create neural network with zero outputs.");

		m_dInputs.reserve(N_inputs);
		for(unsigned long i = 0; i < N_inputs; i++)
		{
			m_dInputs.push_back(inputMinValue);
		}

		m_dOutputs.reserve(N_outputs);
		for(unsigned long i = 0; i < N_outputs; i++)
		{
			m_dOutputs.push_back(outputMinValue);
		}

		m_neurons.reserve(N_neurons);
		for (unsigned long i = 0; i < N_neurons; i++)
		{
			m_neurons.push_back(Neuron(N_neurons + N_inputs));
		}

		m_output_nodes.reserve(N_outputs);
		for (unsigned long i = 0; i < N_outputs; i++)
		{
			m_output_nodes.push_back(Output_node(N_neurons));
		}
	}


	Network::~Network(void)
	{
		m_dInputs.clear();
		m_dOutputs.clear();
		m_neurons.clear();
		m_output_nodes.clear();
	}


	unsigned long Network::get_num_inputs(void) const
	{
		return m_dInputs.size();
	}


	void Network::set_input(const double new_input, const unsigned long indx)
	{
		if((new_input < inputMinValue) || (new_input > inputMaxValue)) throw Network_exception("New network's input has invalid value.");
		if(indx >= m_dInputs.size()) throw Network_exception("Network input index out of range.");

		m_dInputs[indx] = new_input;
	}


	unsigned long Network::get_num_outputs(void) const
	{
		return m_dOutputs.size();
	}


	double Network::get_output(const unsigned long indx) const
	{
		if(indx >= m_dOutputs.size()) throw Network_exception("Network output index out of range.");
		return m_dOutputs[indx];
	}


	unsigned long Network::get_num_neurons(void) const
	{
		return m_neurons.size();
	}


	// get length of neuron's vector of weights
	unsigned long Network::get_neuron_weights_length(const unsigned long neuron_indx) const
	{
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");

		return m_neurons[neuron_indx].get_weights_length();
	}


	// get value of neuron's weight
	double Network::get_neuron_weight(const unsigned long neuron_indx, const unsigned long weight_indx) const
	{
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");
		if(weight_indx >= m_neurons[neuron_indx].get_weights_length()) throw Network_exception("Network neuron's weight index out of range.");

		return m_neurons[neuron_indx].get_weight(weight_indx);
	}


	// set new weight
	void Network::set_neuron_weight(const double new_weight, const unsigned long neuron_indx, const unsigned long weight_indx)
	{
		if((new_weight < weightMinValue) || (new_weight > weightMaxValue)) throw Network_exception("New network neuron's weight has invalid value.");
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");
		if(weight_indx >= m_neurons[neuron_indx].get_weights_length()) throw Network_exception("Network neuron's weight index out of range.");

		m_neurons[neuron_indx].set_weight(new_weight, weight_indx);
	}


	double Network::get_neuron_treshold(const unsigned long neuron_indx) const
	{
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");

		return m_neurons[neuron_indx].get_treshold();
	}


	void Network::set_neuron_treshold(const double new_treshold, const unsigned long neuron_indx)
	{
		if((new_treshold < tresholdMinValue) || (new_treshold > static_cast<double>(m_neurons.size() + m_dInputs.size()))) throw Network_exception("New network neuron's treshold has invalid value.");
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");

		m_neurons[neuron_indx].set_treshold(new_treshold);
	}


	double Network::get_neuron_steepness(const unsigned long neuron_indx) const
	{
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");

		return m_neurons[neuron_indx].get_steepness();
	}


	void Network::set_neuron_steepness(const double new_steepness, const unsigned long neuron_indx)
	{
		if((new_steepness < steepnessMinValue) || (new_steepness > steepnessMaxValue)) throw Network_exception("New network neuron's steepness has invalid value.");
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");

		m_neurons[neuron_indx].set_steepness(new_steepness);
	}


	double Network::get_neuron_simetricity(const unsigned long neuron_indx) const
	{
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");

		return m_neurons[neuron_indx].get_simetricity();
	}


	void Network::set_neuron_simetricity(const double new_simetricity, const unsigned long neuron_indx)
	{
		if((new_simetricity < simetricityMinValue) || (new_simetricity > simetricityMaxValue)) throw Network_exception("New network neuron's simetricity has invalid value.");
		if(neuron_indx >= m_neurons.size()) throw Network_exception("Network neuron index out of range.");

		m_neurons[neuron_indx].set_simetricity(new_simetricity);
	}


	unsigned long Network::get_num_output_nodes(void) const
	{
		return m_output_nodes.size();
	}


	// get length of output node's vector of weights
	unsigned long Network::get_output_node_weights_length(const unsigned long output_node_indx) const
	{
		if(output_node_indx >= m_output_nodes.size()) throw Network_exception("Network output node index out of range.");

		return m_output_nodes[output_node_indx].get_weights_length();
	}


	double Network::get_output_node_weight(const unsigned long output_node_indx, const unsigned long weight_indx) const
	{
		if(output_node_indx >= m_output_nodes.size()) throw Network_exception("Network output node index out of range.");
		if(weight_indx >= m_output_nodes[output_node_indx].get_weights_length()) throw Network_exception("Network output node's weight index out of range.");

		return m_output_nodes[output_node_indx].get_weight(weight_indx);
	}


	void Network::set_output_node_weight(const double new_weight, const unsigned long output_node_indx, const unsigned long weight_indx)
	{
		if((new_weight < weightMinValue) || (new_weight > weightMaxValue)) throw Network_exception("New network output node's weight has invalid value.");
		if(output_node_indx >= m_output_nodes.size()) throw Network_exception("Network output node index out of range.");
		if(weight_indx >= m_output_nodes[output_node_indx].get_weights_length()) throw Network_exception("Network output node's weight index out of range.");

		m_output_nodes[output_node_indx].set_weight(new_weight, weight_indx);
	}


	// calculate new output values from current input values
	void Network::calculate(void)
	{
		std::vector<double> neuron_inputs;
		neuron_inputs.reserve(m_neurons.size() + m_dInputs.size());
		for(unsigned long i = 0; i < m_neurons.size(); i++)
		{
			neuron_inputs.push_back(m_neurons[i].get_output());
		}
		neuron_inputs.insert(neuron_inputs.end(), m_dInputs.begin(), m_dInputs.end());

		for(unsigned long i = 0; i < m_neurons.size(); i++)
		{
			m_neurons[i].calculate(neuron_inputs);
		}
		for(unsigned long i = 0; i < m_neurons.size(); i++)
		{
			m_neurons[i].propagate();
		}


		std::vector<double> neuron_outputs;
		neuron_outputs.reserve(m_neurons.size());
		for(unsigned long i = 0; i < m_neurons.size(); i++)
		{
			neuron_outputs.push_back(m_neurons[i].get_output());
		}

		for(unsigned long i = 0; i < m_output_nodes.size(); i++)
		{
			m_dOutputs[i] = m_output_nodes[i].calculate(neuron_outputs);
		}
	}


	// reset inputs, outputs and neuron outputs and temp_outputs
	void Network::reset(void)
	{
		for(unsigned long i = 0; i < m_dInputs.size(); i++)
		{
			m_dInputs[i] = 0.0;
		}

		for(unsigned long i = 0; i < m_dOutputs.size(); i++)
		{
			m_dOutputs[i] = 0.0;
		}

		for (unsigned long i = 0; i < m_neurons.size(); i++)
		{
			m_neurons[i].reset();
		}
	}
};