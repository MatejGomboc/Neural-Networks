// neural_networks_testing.cpp : Defines the entry point for the console application.

#include "targetver.h"
#include <iostream>
#include <exception>

#include "debug_nn_util.h"
#include "debug_rand_gen.h"
#include "debug_neuron.h"
#include "debug_output_node.h"
#include "debug_network.h"
#include "debug_member.h"
#include "debug_population.h"

#include <memory>

using namespace Neural_networks;

int main(int argc, char* argv[])
{
	std::vector<Member> sweepers;
	sweepers.push_back(Member(1,1,1));

	Population pop(Member::convert_to_pointers(sweepers), Mutation_params());

	sweepers[0].m_dFitness = 1.0;
	pop.m_pMembers[0]->m_dFitness = 0.5;

	while(true);

	while(true)
	{
		std::cout << "Started debuging nn_util." << std::endl;
		try
		{
			Debug::debug_nn_util();
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			while(true);
		}
		std::cout << "Debuging nn_util successful." << std::endl << std::endl;

		std::cout << "Started debuging random generator." << std::endl;
		try
		{
			Debug::debug_rand_gen_double("rand_test_output_histogram_double.csv");
			Debug::debug_rand_gen_unsigned_long("rand_test_output_histogram_int.csv");
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			while(true);
		}
		std::cout << "Debuging random generator successful." << std::endl << std::endl;

		std::cout << "Started debuging Neuron class." << std::endl;
		try
		{
			Debug::debug_neuron();
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			while(true);
		}
		std::cout << "Debuging Neuron class successful." << std::endl << std::endl;

		std::cout << "Started debuging Output node class." << std::endl;
		try
		{
			Debug::debug_output_node();
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			while(true);
		}
		std::cout << "Debuging Output node class successful." << std::endl << std::endl;

		std::cout << "Started debuging Network class." << std::endl;
		try
		{
			Debug::debug_network();
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			while(true);
		}
		std::cout << "Debuging Network class successful." << std::endl << std::endl;

		std::cout << "Started debuging Member class." << std::endl;
		try
		{
			Debug::debug_member();
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			while(true);
		}
		std::cout << "Debuging Member class successful." << std::endl << std::endl;

		/*std::cout << "Started debuging Population class." << std::endl;
		try
		{
			Debug::debug_population();
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			while(true);
		}
		std::cout << "Debuging Population class successful." << std::endl << std::endl;*/

		//while(true);
	}
	return 0;
}

