#include "stdafx.h"
#include "CParams.h"
#include <fstream>
#include "../code/population.h"

using namespace std;

//global constants
const double CParams::dPi = 3.14159265358979;
const double CParams::dHalfPi = dPi / 2.0;
const double CParams::dTwoPi = dPi * 2.0;
const int CParams::iNumInputs = 4;
const int CParams::iNumOutputs = 2;

//ctor
CParams::CParams(void)
{
	WindowWidth            = 400;
	WindowHeight           = 400;

	//because we will always be loading in the settings from an ini file
	//we can just initialize everything to zero

	fFramesPerSecond       = 0;
	iNumTicks              = 0;

	iNumNeurons            = 0;

	dMaxTurnRate           = 0;
	dMaxSpeed              = 0;

	iSweeperScale          = 0;
	dMineScale             = 0;
	iNumSweepers           = 0;
	iNumMines              = 0;

	stMutationParams.mut_probability_neuron_weight = 0;
	stMutationParams.mut_probability_output_weight = 0;

	stMutationParams.mut_probability_activ_treshold = 0;
	stMutationParams.mut_probability_activ_steepness = 0;
	stMutationParams.mut_probability_activ_simetricity = 0;

	if(!LoadInParameters("params.ini"))
	{
		MessageBox(NULL, (LPCWSTR)"Cannot find ini file!", (LPCWSTR)"Error", 0);
	}
}

//this function loads in the parameters from a given file name. Returns
//false if there is a problem opening the file.
bool CParams::LoadInParameters(char* szFileName)
{
	ifstream file(szFileName);

	//check if file exists
	if (!file) return false;

	//load in from the file
	char ParamDescription[40];

	file >> ParamDescription;
	file >> WindowWidth;
	file >> ParamDescription;
	file >> WindowHeight;

	file >> ParamDescription;
	file >> fFramesPerSecond;
	file >> ParamDescription;
	file >> iNumTicks;

	file >> ParamDescription;
	file >> iNumNeurons;
	
	file >> ParamDescription;
	file >> dMaxTurnRate;
	file >> ParamDescription;
	file >> dMaxSpeed;

	file >> ParamDescription;
	file >> iSweeperScale;
	file >> ParamDescription;
	file >> dMineScale;
	file >> ParamDescription;
	file >> iNumSweepers;
	file >> ParamDescription;
	file >> iNumMines;

	file >> ParamDescription;
	file >> stMutationParams.mut_probability_neuron_weight;
	file >> ParamDescription;
	file >> stMutationParams.mut_probability_output_weight;

	file >> ParamDescription;
	file >> stMutationParams.mut_probability_activ_treshold;
	file >> ParamDescription;
	file >> stMutationParams.mut_probability_activ_steepness;
	file >> ParamDescription;
	file >> stMutationParams.mut_probability_activ_simetricity;

	return true;
}