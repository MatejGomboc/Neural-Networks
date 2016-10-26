#include "debug.h"
#include "constants.h"
#include "rand_gen.h"
#include "neuron.h"
#include "output_node.h"
#include "network.h"

#include <iostream>
#include <fstream>
#include <vector>

namespace neural_networks
{
	namespace debug
	{
		const long N_bins = 100;

		static void bining(std::vector<long> &histogram, const double new_value)
		{
			//std::cout << new_value << std::endl;
			long i_bin = static_cast<long>(static_cast<double>(N_bins) * (new_value - min_double) / (max_double - min_double));
			if (i_bin == N_bins) i_bin--;
			histogram[i_bin] ++;
		}

		static void bining(std::vector<long> &histogram, const int new_value)
		{
			//std::cout << new_value << std::endl;
			long i_bin = static_cast<long>(N_bins * (new_value - min_int) / (max_int - min_int));
			if (i_bin == N_bins) i_bin--;
			//std::cout << "i_bin:" << i_bin << std::endl;
			histogram[i_bin] ++;
		}


		void debug_rand_gen_double(const std::string file_name)
		{
			long N_runs = 100000;

			//std::cout << "Num of runs:";
			//std::cin >> N_runs;

			std::vector<long> histogram;
			histogram.resize(N_bins);

			for (long i = 0; i < N_bins; i++)
			{
				histogram[i] = 0;
			}

			for (long i_run = 0; i_run < N_runs; i_run++)
			{
				bining(histogram, random_double());
			}

			std::ofstream file;
			// open for writing, clear previous content
			file.open (file_name, std::ios::out | std::ios::trunc);

			double bin_value = 0.0;

			for (long i = 0; i < N_bins; i++)
			{
				bin_value = min_double + static_cast<double>(i) * (max_double - min_double) / static_cast<double>(N_bins);
				file << bin_value << ";" << histogram[i] << std::endl;
			}

			histogram.clear();
			file.close();
		}


		void debug_rand_gen_int(const std::string file_name)
		{
			long N_runs = 100000;

			//std::cout << "Num of runs:";
			//std::cin >> N_runs;

			std::vector<long> histogram;
			histogram.resize(N_bins);

			for (long i = 0; i < N_bins; i++)
			{
				histogram[i] = 0;
			}

			for (long i_run = 0; i_run < N_runs; i_run++)
			{
				//std::cout << "i_run" << i_run << std::endl;
				bining(histogram, random_int());
			}

			std::ofstream file;
			// open for writing, clear previous content
			file.open (file_name, std::ios::out | std::ios::trunc);

			long bin_value = 0;

			for (long i = 0; i < N_bins; i++)
			{
				bin_value = min_int + i * (max_int - min_int) / N_bins;
				file << bin_value << ";" << histogram[i] << std::endl;
			}

			histogram.clear();
			file.close();
		}


		void debug_neuron(void)
		{
			const unsigned long N_weights = 100;

			Neuron test_neuron(N_weights);

			debug_neuron(N_weights, test_neuron);
		}

		void debug_neuron(const unsigned long N_weights, const Neuron &test_neuron)
		{
			if((test_neuron.m_dOutput > 1.0) || (test_neuron.m_dOutput < 0.0)) throw "Invalid value of neuron's output.";
			if((test_neuron.m_dTemp > 1.0) || (test_neuron.m_dTemp < 0.0)) throw "Invalid value of neuron's temporal output value.";

			if(test_neuron.m_vdWeights.size() != N_weights) throw "Invalid number of weights in neuron.";

			if((test_neuron.m_dTreshold > static_cast<double>(test_neuron.m_vdWeights.size())) ||
				(test_neuron.m_dTreshold < 0.0)) throw "Invalid value of neuron's treshold value.";

			if((test_neuron.m_dSteepness > max_double) || (test_neuron.m_dSteepness < min_double)) throw "Invalid value of neuron's steepness value.";

			if((test_neuron.m_dSimetricity > 1.0) || (test_neuron.m_dSimetricity < 0.0)) throw "Invalid value of neuron's simetricity value.";

			for (unsigned long i = 0; i < test_neuron.m_vdWeights.size(); i++)
			{
				if((test_neuron.m_vdWeights[i] > 1.0) || (test_neuron.m_vdWeights[i] < 0.0)) throw "Invalid value of neuron's weight.";
			}
		}


		void debug_output_node(void)
		{
			const unsigned long N_outputs = 100;

			Output_node test_output_node(N_outputs);

			debug_output_node(N_outputs, test_output_node);
		}

		void debug_output_node(const unsigned long N_neurons, const Output_node &test_output_node)
		{
			if(test_output_node.m_vdWeights.size() != N_neurons) throw "Invalid number of weights in output node.";

			for (unsigned long i = 0; i < test_output_node.m_vdWeights.size(); i++)
			{
				if((test_output_node.m_vdWeights[i] > 1.0) || (test_output_node.m_vdWeights[i] < 0.0)) throw "Invalid value of output node's weight.";
			}
		}


		void debug_network(void)
		{
			const unsigned long N_inputs = 10;
			const unsigned long N_neurons = 100;
			const unsigned long N_outputs = 5;

			Network test_network(N_inputs, N_neurons, N_outputs);

			debug_network(N_inputs, N_neurons, N_outputs, test_network);
		}


		void debug_network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Network& test_network)
		{
			static int indx_run = 0;

			if(test_network.m_dInputs.size() != N_inputs) throw "Invalid number of inputs in network.";
			if(test_network.m_dOutputs.size() != N_outputs) throw "Invalid number of outputs in network.";
			if(test_network.m_neurons.size() != N_neurons) throw "Invalid number of neurons in network.";
			if(test_network.m_output_nodes.size() != N_outputs) throw "Invalid number of output nodes in network.";

			// generate random values of inputs of network
			for(unsigned long i = 0; i < test_network.m_dInputs.size(); i++)
			{
				test_network.m_dInputs[i] = random_double(0.0, 1.0);
			}

			for(unsigned long i = 0; i < test_network.m_neurons.size(); i++)
			{
				debug_neuron(N_inputs + N_neurons, test_network.m_neurons[i]);
			}

			for(unsigned long i = 0; i < test_network.m_output_nodes.size(); i++)
			{
				debug_output_node(N_neurons, test_network.m_output_nodes[i]);
			}

			for(unsigned long i = 0; i < test_network.m_dOutputs.size(); i++)
			{
				if((test_network.m_dOutputs[i] < 0.0) || (test_network.m_dOutputs[i] > 1.0)) throw "Invalid value of network's output.";
			}

			if(indx_run == 1) return;
			test_network.calculate();
			indx_run++;
			debug_network(N_inputs, N_neurons, N_outputs, test_network);
		}


		extern void debug_member(void)
		{
			const unsigned long N_inputs = 10;
			const unsigned long N_neurons = 100;
			const unsigned long N_outputs = 5;

			Member test_member(N_inputs, N_neurons, N_outputs);

			debug_member(N_inputs, N_neurons, N_outputs, test_member);
		}


		extern void debug_member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Member& test_member)
		{
			debug_network(N_inputs, N_neurons, N_outputs, test_member.m_brain);

			if((test_member.m_dFitness < 0.0) || (test_member.m_dFitness > 1.0)) throw "Invalid value of member's fitness.";
		}
	};
};