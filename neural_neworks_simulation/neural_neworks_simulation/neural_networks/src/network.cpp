#include "network.h"
#include "neuron.h"
#include "output_node.h"
#include "constants.h"
#include "srestricted.h"
#include <vector>

namespace neural_networks
{
	Network::Network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs)
	{
		if (N_inputs <= 0) throw Network_exception("Cannot create neural network with zero inputs.");
		if (N_outputs <= 0) throw Network_exception("Cannot create neural network with zero outputs.");
		if (N_neurons <= 0) throw Network_exception("Cannot create neural network with zero neurons.");

		m_dInputs.reserve(N_inputs);
		for(unsigned long i = 0; i < N_inputs; i++)
		{
			m_dInputs.push_back(restricted_range::srestricted<double, 0, 1>(0.0));
		}

		m_dOutputs.reserve(N_outputs);
		for(unsigned long i = 0; i < N_outputs; i++)
		{
			m_dOutputs.push_back(restricted_range::srestricted<double, 0, 1>(0.0));
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


	// calculate new output values from current input values
	void Network::calculate(void)
	{
		test();

		for(unsigned long i = 0; i < m_neurons.size(); i++)
		{
			m_neurons[i].calculate(m_neurons, m_dInputs);
		}

		for(unsigned long i = 0; i < m_neurons.size(); i++)
		{
			m_neurons[i].propagate();
		}

		for(unsigned long i = 0; i < m_output_nodes.size(); i++)
		{
			m_dOutputs[i] = m_output_nodes[i].calculate(m_neurons);
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


	void Network::test(void) const // test neural network for correct number of neurons and output nodes, also test each one of them
	{
		if(m_dInputs.size() == 0)
			throw Network_exception("This neural network has zero inputs.");
		if(m_neurons.size() == 0)
			throw Network_exception("This neural network has zero neurons.");
		if(m_dOutputs.size() == 0)
			throw Network_exception("This neural network has zero outputs.");
		if(m_output_nodes.size() == 0)
			throw Network_exception("This neural network has zero output nodes.");

		if(m_dOutputs.size() != m_output_nodes.size())
			throw Network_exception("Number of outputs of neural network does not match the number of output nodes in this network.");

		for (unsigned long i = 0; i < m_neurons.size(); i++)
		{
			m_neurons[i].test(m_neurons.size() + m_dInputs.size());
		}

		for (unsigned long i = 0; i < m_output_nodes.size(); i++)
		{
			m_output_nodes[i].test(m_neurons.size());
		}
	}
};