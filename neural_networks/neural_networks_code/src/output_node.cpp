#include "output_node.h"
#include "rand_gen.h"
#include "constants.h"

#include <vector>


namespace Neural_networks
{
	Output_node::Output_node(const unsigned long N_inputs)
	{
		if (N_inputs <= 0) throw Output_node_exception("Cannot create an output node with zero inputs.");

		m_vdWeights.reserve(N_inputs);

		for (unsigned long i = 0; i < N_inputs; i++)
		{
			m_vdWeights.push_back(random_double(weightMinValue, weightMaxValue));
		}
	}


	Output_node::~Output_node(void)
	{
		m_vdWeights.clear();
	}


	// get length of vector of weights
	unsigned long Output_node::get_weights_length(void) const
	{
		return m_vdWeights.size();
	}


	// get values of ouput node's weights
	double Output_node::get_weight(const unsigned long indx) const
	{
		if(indx >= m_vdWeights.size()) throw Output_node_exception("Output node weight index out of range.");

		return m_vdWeights[indx]; 
	}


	// set new weights
	void Output_node::set_weight(const double new_weight, const unsigned long indx)
	{
		if((new_weight < weightMinValue) || (new_weight > weightMaxValue)) throw Output_node_exception("New output node's weight has invalid value.");
		if(indx >= m_vdWeights.size()) throw Output_node_exception("Output node weight index out of range.");

		m_vdWeights[indx] = new_weight;
	}


	 // calculate new output value from inputs
	double Output_node::calculate(const std::vector<double> &inputs) const
	{
		if(inputs.size() != m_vdWeights.size()) throw Output_node_exception("Invaid number of inputs to this output node.");

		double summ = 0.0; // (0.0 - N_neurons)

		for(unsigned long i = 0; i < inputs.size(); i++)
		{
			summ += inputs[i] * m_vdWeights[i];
		}

		return (summ / static_cast<double>(inputs.size()));
	}
};