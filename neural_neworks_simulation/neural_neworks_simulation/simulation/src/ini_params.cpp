#include "ini_params.h"
#include <fstream>


namespace Simulation
{
	//because we will always be loading in the settings from an ini file
	//we can just initialize everything to zero
	const double Ini_params::m_dPi       = 3.14159265358979;
	const double Ini_params::m_dHalfPi   = m_dPi / 2.0;
	const double Ini_params::m_dTwoPi    = m_dPi * 2.0;


	//this function loads in the parameters from a given file name. Returns
	//false if there is a problem opening the file.
	void Ini_params::loadIniParameters(void)
	{
		std::ifstream grab("params.ini");

		//check file exists
		if (!grab) throw("Cannot find ini file.");

		//load in from the file
		char ParamDescription[40];

		grab >> ParamDescription;
		grab >> m_fFramesPerSecond;
		grab >> ParamDescription;
		grab >> m_dMaxTurnRate;
		grab >> ParamDescription;
		grab >> m_dMaxSpeed;
		grab >> ParamDescription;
		grab >> m_iSweeperScale;
		grab >> ParamDescription;
		grab >> m_iNumMines;
		grab >> ParamDescription;
		grab >> m_iNumSweepers;
		grab >> ParamDescription;
		grab >> m_iNumTicks;
		grab >> ParamDescription;
		grab >> m_dMineScale;
	}


	Ini_params::Ini_params(void) :
	m_iWindowWidth(400),
	m_iWindowHeight(400),
	m_fFramesPerSecond(0.0f),
	m_dMaxTurnRate(0.0),
	m_dMaxSpeed(0.0),
	m_iSweeperScale(0),
	m_iNumSweepers(0),
	m_iNumMines(0),
	m_iNumTicks(0),
	m_dMineScale(0.0)
	{
		loadIniParameters();
	}
}