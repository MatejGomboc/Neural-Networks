#pragma once

#include <vector>
#include "matrix2d.h"
#include "vector2d.h"


class Mine_sweeper //: public neural_networks::Member
{
private:
	//it's position in the world
	Vector2D m_vPosition;

	//orientation and speed of the sweeper
	//to store outputs from the NN
	double m_dRotation;
	double m_dSpeed;

	//the sweeper's score 
	double m_dScore;

	unsigned long m_ulClosestMine;

public:
	Mine_sweeper();

	void reset();

	//updates the NN with information from the sweeper's enviroment
	void update(const std::vector<Vector2D>& mines);

	//used to transform the sweepers vertices prior to rendering
	void worldTransform(const double sweeper_scale);

	//returns a vector to the closest mine
	Vector2D getClosestMine(const std::vector<Vector2D>& mines);

	//checks to see if the minesweeper has 'collected' a mine
	bool checkCollision(const std::vector<Vector2D>& mines, const double mine_size);
};