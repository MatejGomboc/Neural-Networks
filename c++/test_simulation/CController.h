#ifndef CCONTROLLER_H
#define CCONTROLLER_H

//------------------------------------------------------------------------
//
//	Name: CController.h
//
//  Desc: Controller class for the simulation.
//
//------------------------------------------------------------------------

#include <windows.h>
#include <vector>
#include "CMineSweeper.h"
#include "CSweeperPopulation.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"

using namespace std;


class CController
{
private:
    //storage for the population of minesweepers
    CSweeperPopulation   m_vecSweepers;

	//and the mines
	vector<SVector2D>    m_vecMines;

	//vertex buffer for the sweeper shape's vertices
	vector<SPoint>		 m_SweeperVB;

	//vertex buffer for the mine shape's vertices
	vector<SPoint>		 m_MineVB;

	//stores the average score per generation for use 
	//in graphing.
	vector<double>		 m_vecAvScore;

	//stores the best score per generation
	vector<double>		 m_vecBestScore;

	//pens we use for the stats ploting
	HPEN				 m_RedPen;
	HPEN				 m_BluePen;
	HPEN				 m_GreenPen;
	HPEN				 m_OldPen;

	//toggles the speed at which the simulation runs
	bool				 m_bFastRender;
	
	//cycles per generation
	int					 m_iTicks;

	//generation counter
	int					 m_iGenerations;

	//this function plots a graph of the average and best scores
	//over the course of a run
	void PlotStats(HWND hwndMain, HDC surface);

public:

	CController::CController(HWND hwndMain, CParams* pParams);
	~CController();

	void Render(HDC surface);
	void WorldTransform(vector<SPoint> &VBuffer, SVector2D vPos, CParams pParams);
	bool Update();

	//accessor methods
	inline bool FastRender() const
	{
		return m_bFastRender;
	}

	inline void	FastRender(bool arg)
	{
		m_bFastRender = arg;
	}

	inline void	FastRenderToggle()
	{
		m_bFastRender = !m_bFastRender;
	}
};

#endif
	
