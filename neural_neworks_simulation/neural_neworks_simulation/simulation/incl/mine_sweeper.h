#pragma once

#include <vector>
#include <cmath>

#include "utils.h"
#include "matrix2d.h"
#include "vector2d.h"
#include "ini_params.h"
#include "member.h"


class Mine_sweeper : public neural_networks::Member
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

public:
	Mine_sweeper();

	void reset();

	//updates the NN with information from the sweeper's enviroment
	void update(const std::vector<Vector2D>& mines);

	//used to transform the sweepers vertices prior to rendering
	void worldTransform(void);

	//returns a vector to the closest mine
	SVector2D	GetClosestMine(vector<SVector2D> &objects);

	//checks to see if the minesweeper has 'collected' a mine
	int       CheckForMine(vector<SVector2D> &mines, double size);

	//-------------------accessor functions
	SVector2D	Position()const{return m_vPosition;}

	void			IncrementFitness(){++m_dFitness;}

	double		Fitness()const{return m_dFitness;}

	void      PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}

	int       GetNumberOfWeights()const{return m_ItsBrain.GetNumberOfWeights();}
};