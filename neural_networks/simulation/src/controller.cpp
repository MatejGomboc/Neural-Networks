#include "controller.h"
#include "mine_sweeper.h"
#include "mine.h"
#include "ini_params.h"
#include "population.h"


namespace Simulation
{
	//---------------------------------------constructor---------------------
	//
	// Initilaize the sweepers, their brains and the mines.
	//
	//-----------------------------------------------------------------------
	Controller::Controller(const Ini_params& params) :
		m_ulTicks(0),
		m_ulGenerations(0)
	{
		//let's create the mine sweepers
		for (unsigned long i = 0; i < params.m_ulNumSweepers; ++i)
		{
			m_sweepers.push_back(Mine_sweeper(params.m_ulNumNeurons));
		}

		//initialize mines in random positions within the application window
		for (unsigned long i = 0; i < params.m_ulNumMines; ++i)
		{
			m_mines.push_back(Mine());
		}
	}


	//-------------------------------------Update-----------------------------
	//
	// This is the main workhorse. The entire simulation is controlled from here.
	//
	//-------------------------------------------------------------------------
	void Controller::update(const Ini_params& params)
	{
		//Run the sweepers through m_ulNumTicks amount of cycles. During
		//this loop each sweepers NN is constantly updated with the appropriate
		//information from its surroundings. The output from the NN is obtained
		//and the sweeper is moved. If it encounters a mine it's fitness is
		//updated appropriately.

		if (m_ulTicks++ < params.m_ulNumTicks)
		{
			for (unsigned long i = 0; i < m_sweepers.size(); ++i)
			{
				//update the NN and position
				m_sweepers[i].update(m_mines, params);

				//see if it has found a mine
				m_sweepers[i].checkCollision(m_mines, params.m_dMineSize);
			}
		}

		//Another generation has been completed.
		//Time to run the GA and update the sweepers' NNs.
		else
		{
			//update the stats to be used in our stat window

			//increment the generation counter
			++m_ulGenerations;

			//reset cycles
			m_ulTicks = 0;

			//run the GA to create a new population

			//reset sweepers positions and speeds
			for (unsigned long i = 0; i < m_sweepers.size(); ++i)
			{
				m_sweepers[i].reset();
			}
		}
	}
}
