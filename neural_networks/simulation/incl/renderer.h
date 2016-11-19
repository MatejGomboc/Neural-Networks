#pragma once

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <windows.h>

#include "utils.h"
#include "matrix2d.h"
#include "vector2d.h"


namespace Simulation
{
	class Renderer
	{
	private:
		//vertex buffer for the sweeper shape's vertices
		vector<SPoint> m_SweeperVB;

		//vertex buffer for the mine shape's vertices
		vector<SPoint> m_MineVB;

		//pens we use for the stats
		HPEN m_RedPen;
		HPEN m_BluePen;
		HPEN m_GreenPen;
		HPEN m_OldPen;

		//handle to the application window
		HWND m_hwndMain;

		//window dimensions
		int cxClient, cyClient;

		//toggles the speed at which the simulation runs
		bool m_bFastRender;

		//this function plots a graph of the average and best fitnesses
		//over the course of a run
		void PlotStats(HDC surface);
	public:
		Renderer(HWND hwndMain);

		~Renderer();

		void Render(HDC surface);

		void WorldTransform(vector<SPoint> &VBuffer, SVector2D vPos);
	};
}