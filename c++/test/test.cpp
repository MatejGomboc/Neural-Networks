#include <iostream>
#include <stdlib.h>
#include "../code/population.h"
#include "../code/rand_gen.h"

using namespace std;
using namespace neural_networks;

int main(void)
{
	rand_gen rnd;

	cout << rnd.random_double() << endl;
	cout << rnd.random_double() << endl;
	cout << rnd.random_double() << endl;
    	cout << rnd.random_double() << endl;
	cout << rnd.random_double() << endl;

	rand_gen rnd2;

	cout << rnd2.random_double() << endl;
	cout << rnd2.random_double() << endl;
	cout << rnd2.random_double() << endl;
	cout << rnd2.random_double() << endl;
	cout << rnd2.random_double() << endl;

	t_mut_params par;
	par.mut_probability_activ_simetricity = 0.2;
	par.mut_probability_activ_steepness = 0.2;
	par.mut_probability_activ_treshold = 0.2;
	par.mut_probability_neuron_weight = 0.2;
	par.mut_probability_output_weight = 0.2;

	population pop(2, 3, 10, 3, par);

    	cout << "loaded" << endl;

	system("PAUSE");

	cout << endl << "mut params:" << endl << endl;
	cout << "sim:" << pop.mutation_params.mut_probability_activ_simetricity << endl;
	cout << "stp:" << pop.mutation_params.mut_probability_activ_steepness << endl;
	cout << "thd:" << pop.mutation_params.mut_probability_activ_treshold << endl;
	cout << "nwt:" << pop.mutation_params.mut_probability_neuron_weight << endl;
	cout << "owt:" << pop.mutation_params.mut_probability_output_weight << endl;

	system("PAUSE");

	for(unsigned i = 0; i < pop.members.size(); i++)
	{
		cout << endl << endl << "member[" << i << "]:" << endl;

		system("PAUSE");

		cout << endl << "fit:" << pop.members[i].fitness << endl << endl;

		cout << "inputs:" << endl;
		for(unsigned j = 0; j < pop.members[i].brain.inputs.size(); j++)
		{
			cout << pop.members[i].brain.inputs[j] << endl;
		}

		system("PAUSE");

		cout << endl << "outputs:" << endl;
		for(unsigned j = 0; j < pop.members[i].brain.outputs.size(); j++)
		{
			cout << pop.members[i].brain.outputs[j] << endl;
		}

		cout << endl;

		system("PAUSE");

		for(unsigned j = 0; j < pop.members[i].brain.neurons.size(); j++)
		{
			cout << "neuron[" << j << "]:" << endl << endl;

			cout << "N_weights:" << pop.members[i].brain.neurons[j].weights.size() << endl << endl;

			cout << "sim:" << pop.members[i].brain.neurons[j].simetricity << endl;
			cout << "stp:" << pop.members[i].brain.neurons[j].steepness << endl;
			cout << "thd:" << pop.members[i].brain.neurons[j].treshold << endl;
			cout << endl;

			for(unsigned k = 0; k < pop.members[i].brain.neurons[j].weights.size(); k++)
			{
				cout << "weight[" << k << "]:" << pop.members[i].brain.neurons[j].weights[k] << endl;
			}

			cout << endl;

			system("PAUSE");
		}

		for(unsigned j = 0; j < pop.members[i].brain.output_nodes.size(); j++)
		{
			cout << "ouput_node[" << j << "]:" << endl << endl;

			cout << "N_weights:" << pop.members[i].brain.output_nodes[j].weights.size() << endl << endl;

			for(unsigned k = 0; k < pop.members[i].brain.neurons[j].weights.size(); k++)
			{
				cout << "weight[" << k << "]:" 
					<< pop.members[i].brain.neurons[j].weights[k] << endl;
			}

			cout << endl;

			system("PAUSE");
		}
	}

	pop.mutate();


	cout << "mutated" << endl;

	system("PAUSE");

	cout << endl << "mut params:" << endl << endl;
	cout << "sim:" << pop.mutation_params.mut_probability_activ_simetricity << endl;
	cout << "stp:" << pop.mutation_params.mut_probability_activ_steepness << endl;
	cout << "thd:" << pop.mutation_params.mut_probability_activ_treshold << endl;
	cout << "nwt:" << pop.mutation_params.mut_probability_neuron_weight << endl;
	cout << "owt:" << pop.mutation_params.mut_probability_output_weight << endl;

	system("PAUSE");

	for(unsigned i = 0; i < pop.members.size(); i++)
	{
		cout << endl << endl << "member[" << i << "]:" << endl;

		system("PAUSE");

		cout << endl << "fit:" << pop.members[i].fitness << endl << endl;

		cout << "inputs:" << endl;
		for(unsigned j = 0; j < pop.members[i].brain.inputs.size(); j++)
		{
			cout << pop.members[i].brain.inputs[j] << endl;
		}

		system("PAUSE");

		cout << endl << "outputs:" << endl;
		for(unsigned j = 0; j < pop.members[i].brain.outputs.size(); j++)
		{
			cout << pop.members[i].brain.outputs[j] << endl;
		}

		cout << endl;

		system("PAUSE");

		for(unsigned j = 0; j < pop.members[i].brain.neurons.size(); j++)
		{
			cout << "neuron[" << j << "]:" << endl << endl;

			cout << "N_weights:" << pop.members[i].brain.neurons[j].weights.size() << endl << endl;

			cout << "sim:" << pop.members[i].brain.neurons[j].simetricity << endl;
			cout << "stp:" << pop.members[i].brain.neurons[j].steepness << endl;
			cout << "thd:" << pop.members[i].brain.neurons[j].treshold << endl;
			cout << endl;

			for(unsigned k = 0; k < pop.members[i].brain.neurons[j].weights.size(); k++)
			{
				cout << "weight[" << k << "]:" << pop.members[i].brain.neurons[j].weights[k] << endl;
			}

			cout << endl;

			system("PAUSE");
		}

		for(unsigned j = 0; j < pop.members[i].brain.output_nodes.size(); j++)
		{
			cout << "ouput_node[" << j << "]:" << endl << endl;

			cout << "N_weights:" << pop.members[i].brain.output_nodes[j].weights.size() << endl << endl;

			for(unsigned k = 0; k < pop.members[i].brain.neurons[j].weights.size(); k++)
			{
				cout << "weight[" << k << "]:" 
					<< pop.members[i].brain.neurons[j].weights[k] << endl;
			}

			cout << endl;

			system("PAUSE");
		}
	}


	pop.mate();


	cout << "mated" << endl;

	system("PAUSE");

	cout << endl << "mut params:" << endl << endl;
	cout << "sim:" << pop.mutation_params.mut_probability_activ_simetricity << endl;
	cout << "stp:" << pop.mutation_params.mut_probability_activ_steepness << endl;
	cout << "thd:" << pop.mutation_params.mut_probability_activ_treshold << endl;
	cout << "nwt:" << pop.mutation_params.mut_probability_neuron_weight << endl;
	cout << "owt:" << pop.mutation_params.mut_probability_output_weight << endl;

	system("PAUSE");

	for(unsigned i = 0; i < pop.members.size(); i++)
	{
		cout << endl << endl << "member[" << i << "]:" << endl;

		system("PAUSE");

		cout << endl << "fit:" << pop.members[i].fitness << endl << endl;

		cout << "inputs:" << endl;
		for(unsigned j = 0; j < pop.members[i].brain.inputs.size(); j++)
		{
			cout << pop.members[i].brain.inputs[j] << endl;
		}

		system("PAUSE");

		cout << endl << "outputs:" << endl;
		for(unsigned j = 0; j < pop.members[i].brain.outputs.size(); j++)
		{
			cout << pop.members[i].brain.outputs[j] << endl;
		}

		cout << endl;

		system("PAUSE");

		for(unsigned j = 0; j < pop.members[i].brain.neurons.size(); j++)
		{
			cout << "neuron[" << j << "]:" << endl << endl;

			cout << "N_weights:" << pop.members[i].brain.neurons[j].weights.size() << endl << endl;

			cout << "sim:" << pop.members[i].brain.neurons[j].simetricity << endl;
			cout << "stp:" << pop.members[i].brain.neurons[j].steepness << endl;
			cout << "thd:" << pop.members[i].brain.neurons[j].treshold << endl;
			cout << endl;

			for(unsigned k = 0; k < pop.members[i].brain.neurons[j].weights.size(); k++)
			{
				cout << "weight[" << k << "]:" << pop.members[i].brain.neurons[j].weights[k] << endl;
			}

			cout << endl;

			system("PAUSE");
		}

		for(unsigned j = 0; j < pop.members[i].brain.output_nodes.size(); j++)
		{
			cout << "ouput_node[" << j << "]:" << endl << endl;

			cout << "N_weights:" << pop.members[i].brain.output_nodes[j].weights.size() << endl << endl;

			for(unsigned k = 0; k < pop.members[i].brain.neurons[j].weights.size(); k++)
			{
				cout << "weight[" << k << "]:" 
					<< pop.members[i].brain.neurons[j].weights[k] << endl;
			}

			cout << endl;

			system("PAUSE");
		}
	}


	cout << endl << endl << endl;
	system("PAUSE");

	return 0;
}
