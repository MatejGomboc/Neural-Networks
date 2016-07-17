#ifndef CMINESWEEPER_H
#define CMINESWEEPER_H

//------------------------------------------------------------------------
//
//	Name: CMineSweeper.h
//
//  Desc: Class to create a minesweeper object 
//
//------------------------------------------------------------------------

#include "CParams.h"
#include "SVector2D.h"
#include "SPoint.h"
#include "../code/member.h"

using namespace std;


class CMineSweeper : public neural_networks::member
{
private:
	//its position in the world
	SVector2D		m_vPosition;

	//direction sweeper is facing
	SVector2D		m_vLookAt;

	//its rotation
	double			m_dRotation;
	double			m_dSpeed;

	//to store output from the ANN
	double			m_lTrack, m_rTrack;

	//the sweeper's score 
	unsigned	    m_uiScore;

	//index position of closest mine
	int             m_iClosestMine;

public:
	CMineSweeper(CParams* pParams);

	//updates the ANN with information from the sweepers enviroment
	bool Update(vector<SVector2D> &mines, CParams* pParams);

	//used to transform the sweepers vertices prior to rendering
	void WorldTransform(vector<SPoint> &sweeper, CParams* pParams);

	//returns a vector to the closest mine
	SVector2D GetClosestMine(vector<SVector2D> &objects);

	//checks to see if the minesweeper has 'collected' a mine
	int CheckForMine(vector<SVector2D> &mines, double size);

	//resets the sweepers position, fitness and rotation
	void Reset(CParams* pParams);

	//-------------------accessor functions
	inline SVector2D Position() const
	{
		return m_vPosition;
	}

	inline void IncrementScore()
	{
		++m_uiScore;
	}
};

#endif