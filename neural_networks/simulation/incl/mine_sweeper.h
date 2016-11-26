#pragma once

#include <vector>
#include "vector2d.h"
#include "mine.h"
#include "member.h"
#include "ini_params.h"


namespace Simulation
{
	class Mine_sweeper : private Neural_networks::Member
	{
	public:
		//it's position in the world
		Linear_algebra::Vector2D m_vPosition;

		//orientation and speed of the sweeper
		//to store outputs from the NN
		double m_dRotation;
		double m_dSpeed;

		//the sweeper's score 
		unsigned long m_ulScore;

		//index of the closest mine
		unsigned long m_ulClosestMine;

	public:
		Mine_sweeper(const unsigned long N_neurons);

		virtual void reset(void);

		//updates the NN with information from the sweeper's enviroment
		void update(const std::vector<Mine>& mines, const Ini_params& params);

		//used to transform the sweepers vertices prior to rendering
		void worldTransform(const double sweeper_scale);

		//returns a vector to the closest mine
		Linear_algebra::Vector2D getClosestMine(const std::vector<Mine>& mines);

		//checks to see if the minesweeper has 'collected' a mine
		void checkCollision(std::vector<Mine>& mines, const double mine_size);
	};
};