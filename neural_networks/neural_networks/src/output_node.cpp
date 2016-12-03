#include "output_node.h"
#include "neuron.h"
#include "rand_gen.h"
#include "constants.h"
#include "srestricted.h"
#include <vector>


namespace Neural_networks
{
	Output_node::Output_node(const unsigned long N_neurons)
	{
		if (N_neurons <= 0) throw Output_node_exception("Cannot create an output node with zero inputs.");

		m_vdWeights.reserve(N_neurons);

		for (unsigned long i = 0; i < N_neurons; i++)
		{
			m_vdWeights.push_back(Restricted_range::srestricted<double, 0 ,1>(random_double(0.0, 1.0)));
		}
	}


	Output_node::~Output_node(void)
	{
		//m_vdWeights.clear();
	}


	 // calculate new output value from outputs of neurons
	double Output_node::calculate(const std::vector<Neuron> &neurons) const
	{
		// test output node for valid number of weights
		test(neurons.size());
		
		double summ = 0.0; // (0.0 - N_neurons)

		for(unsigned long i = 0; i < neurons.size(); i++)
		{
			summ += neurons[i].m_dOutput * m_vdWeights[i];
		}

		return (summ / static_cast<double>(neurons.size()));
	}


	// test output node for valid number of weights
	void Output_node::test(const unsigned long N_neurons) const
	{
		if(m_vdWeights.size() == 0)
			throw Output_node_exception("This output node has zero weights.");

		if(N_neurons != m_vdWeights.size())
			throw Output_node_exception("Number of inputs from neurons' outputs does not match the number of weights in output node.");
	}
};