#ifndef CPARAMS_H
#define CPARAMS_H

//------------------------------------------------------------------------
//
//	Name: CParams.h
//
//
//  Desc: Class to hold all the parameters used in this project. The values
//        are loaded in from an .ini file when an instance of the class is
//        created.
//       
//------------------------------------------------------------------------

#include "../code/population.h"

class CParams
{
public:
	//------------------------------------global constants
	static const double dPi;
	static const double dHalfPi;
	static const double dTwoPi;

	//------------------------------------general parameters
	int    WindowWidth;
	int    WindowHeight;

	float  fFramesPerSecond;

	//-------------------------------------used for the neural network
	static const int iNumInputs;
	int    iNumNeurons;
	static const int iNumOutputs;

	//--------------------------------------used to define the sweepers

	//limits how fast the sweepers can turn
	double dMaxTurnRate;

	double dMaxSpeed;

	//for controlling the size
	int   iSweeperScale;

	//--------------------------------------controller parameters
	int    iNumSweepers;

	int    iNumMines;

	//number of time steps we allow for each generation to live
	int    iNumTicks;

	//scaling factor for mines
	double dMineScale;

	//---------------------------------------GA parameters
	neural_networks::t_mut_params stMutationParams;

	//ctor
	CParams(void);

	//this function loads in the parameters from a given file name. Returns
	//false if there is a problem opening the file.
	bool LoadInParameters(char* szFileName);
};

#endif