// neural_networks_debug_project.cpp : Defines the entry point for the console application.
//

#include "targetver.h"

#include "population.h"
#include <vector>
#include <memory>


std::vector<std::shared_ptr<Neural_networks::Member>> p_members;
Neural_networks::Population population(p_members);

int main(int argc, char** argv)
{
	p_members.reserve(100);

	for(unsigned long i = 0; i < 100; i++)
	{
		p_members.push_back(std::shared_ptr<Neural_networks::Member>(new Neural_networks::Member(10, 100, 10)));
	}

	while(true);

	return 0;
}
