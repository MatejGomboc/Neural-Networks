#pragma once


namespace Simulation
{
	class Ini_params
	{
	public:
		//------------------------------------general parameters

		static const double m_dPi;
		static const double m_dHalfPi;
		static const double m_dTwoPi;

		int m_iWindowWidth;
		int m_iWindowHeight;

		float m_fFramesPerSecond;

		//--------------------------------------used to define the sweepers

		//number of neurons in sweeper's brain
		unsigned long m_ulNumNeurons;

		//limits how fast the sweepers can move
		double m_dMaxSpeed;

		//for controlling the size of the sweepers
		double m_dSweeperScale;

		//--------------------------------------controller parameters

		unsigned long m_ulNumSweepers;

		unsigned long m_ulNumMines;

		//number of time steps we allow for each generation to live
		unsigned long m_ulNumTicks;

		//size of mines
		double m_dMineSize;

		//--------------------------------------initialization function

		void loadIniParameters(void);

		Ini_params(void);
	};
};
