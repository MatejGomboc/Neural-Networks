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

		//limits how fast the sweepers can turn
		double m_dMaxTurnRate;

		//limits how fast the sweepers can move
		double m_dMaxSpeed;

		//for controlling the size of the sweepers
		int m_iSweeperScale;

		//--------------------------------------controller parameters

		int m_iNumSweepers;

		int m_iNumMines;

		//number of time steps we allow for each generation to live
		int m_iNumTicks;

		//scaling factor for mines
		double m_dMineScale;

		//--------------------------------------initialization function

		void loadIniParameters(void);

		Ini_params(void);
	};
}
