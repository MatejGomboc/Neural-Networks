#include <iostream>
#include <fstream>
#include "../code/rand_gen.h"

const unsigned long N_bins = 100;

void bining(unsigned long* histogram, double new_value);

int main()
{
	unsigned long N_runs = 100000;

	//std::cout << "Num of runs:";
	//std::cin >> N_runs;

	unsigned long histogram[N_bins];

	for (unsigned long i = 0; i < N_bins; i++)
	{
		histogram[i] = 0;
	}

	neural_networks::rand_gen rand;

	for (unsigned long i_run = 0; i_run < N_runs; i_run++)
	{
		bining(histogram, rand.random_double());
	}

	std::ofstream file;
	// open for writing, clear previous content
	file.open ("output.csv", std::ios::out | std::ios::trunc);

	double bin_value = 0.0;

	for (unsigned long i = 0; i < N_bins; i++)
	{
		bin_value = neural_networks::min_double + (double)i * (neural_networks::max_double - neural_networks::min_double) / (double)N_bins;
		file << bin_value << ";" << histogram[i] << std::endl;
	}

	file.close();

	return 0;
}

void bining(unsigned long* histogram, double new_value)
{
	//std::cout << new_value << std::endl;
	unsigned long i_bin = (unsigned long)((double)N_bins * (new_value - neural_networks::min_double) / (neural_networks::max_double - neural_networks::min_double));
	histogram[i_bin] ++;
}