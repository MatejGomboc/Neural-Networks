#include "ini_params.h"
#include <fstream>
#include <exception>


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
		if (!grab) throw(std::exception("Cannot find ini file."));

		//load in from the file
		char ParamDescription[40];

		grab >> ParamDescription;
		grab >> m_fFramesPerSecond;
		grab >> ParamDescription;
		grab >> m_ulNumNeurons;
		grab >> ParamDescription;
		grab >> m_dMaxSpeed;
		grab >> ParamDescription;
		grab >> m_dSweeperScale;
		grab >> ParamDescription;
		grab >> m_ulNumMines;
		grab >> ParamDescription;
		grab >> m_ulNumSweepers;
		grab >> ParamDescription;
		grab >> m_ulNumTicks;
		grab >> ParamDescription;
		grab >> m_dMineSize;
	}


	Ini_params::Ini_params(void) :
	m_iWindowWidth(400),
	m_iWindowHeight(400),
	m_fFramesPerSecond(0.0f),
	m_ulNumNeurons(0),
	m_dMaxSpeed(0.0),
	m_dSweeperScale(0.0),
	m_ulNumSweepers(0),
	m_ulNumMines(0),
	m_ulNumTicks(0),
	m_dMineSize(0.0)
	{
		loadIniParameters();
	}
}