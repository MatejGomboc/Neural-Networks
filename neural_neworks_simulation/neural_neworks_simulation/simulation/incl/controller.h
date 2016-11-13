#pragma once

#include <vector>
#include "mine_sweeper.h"
#include "mine.h"
#include "ini_params.h"
#include "population.h"


namespace Simulation
{
	class Controller
	{
	private:
		//population of minesweepers
		std::vector<Mine_sweeper> m_sweepers;

		//population of mines
		std::vector<Mine> m_mines;

		//stores the average fitness per generation for use in graphing.
		std::vector<double> m_vdAvgFitness;
	
		//cycles in current generation
		unsigned long m_ulTicks;

		//generation counter
		unsigned long m_ulGenerations;

	public:
		Controller(const Ini_params& params);
	
		void update(const Ini_params& params);
	};
};
