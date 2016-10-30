#include "debug_rand_gen.h"
#include "constants.h"
#include "rand_gen.h"

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
	};
};