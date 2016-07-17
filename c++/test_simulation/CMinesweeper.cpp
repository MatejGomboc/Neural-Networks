#include "CMineSweeper.h"
#include <vector>
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"
#include "SPoint.h"
#include "../code/member.h"

using namespace std;

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CMineSweeper::CMineSweeper(CParams* pParams) : member(pParams->iNumInputs, pParams->iNumNeurons, pParams->iNumOutputs)
{
	m_dRotation    = RandFloat() * CParams::dTwoPi;
	m_lTrack       = 0.16;
	m_rTrack       = 0.16;
	m_uiScore      = 0;
	m_iClosestMine = 0;

	//create a random start position
	m_vPosition = SVector2D((RandFloat() * pParams->WindowWidth), (RandFloat() * pParams->WindowHeight));
}

//-------------------------------------------Reset()--------------------
//
//	Resets the sweepers position, fitness and rotation
//
//----------------------------------------------------------------------
void CMineSweeper::Reset(CParams* pParams)
{
	//reset the sweepers positions
	m_vPosition = SVector2D((RandFloat() * pParams->WindowWidth), (RandFloat() * pParams->WindowHeight));

	//and the score
	m_uiScore = 0;

	//and the rotation
	m_dRotation = RandFloat()*CParams::dTwoPi;

	return;
}

//---------------------WorldTransform--------------------------------
//
//	sets up a translation matrix for the sweeper according to its
//  scale, rotation and position. Returns the transformed vertices.
//-------------------------------------------------------------------
void CMineSweeper::WorldTransform(vector<SPoint> &sweeper, CParams* pParams)
{
	//create the world transformation matrix
	C2DMatrix matTransform;

	//scale
	matTransform.Scale(pParams->iSweeperScale, pParams->iSweeperScale);

	//rotate
	matTransform.Rotate(m_dRotation);

	//and translate
	matTransform.Translate(m_vPosition.x, m_vPosition.y);

	//now transform the ships vertices
	matTransform.TransformSPoints(sweeper);
}

//-------------------------------Update()--------------------------------
//
//	First we take sensor readings and feed these into the sweepers brain.
//
//	The inputs are:
//	
//	A vector to the closest mine (x, y)
//	The sweepers 'look at' vector (x, y)
//
//	We receive two outputs from the brain.. lTrack & rTrack.
//	So given a force for each track we calculate the resultant rotation 
//	and acceleration and apply to current velocity vector.
//
//-----------------------------------------------------------------------
bool CMineSweeper::Update(vector<SVector2D> &mines, CParams* pParams)
{
	//get vector to closest mine
	SVector2D vClosestMine = GetClosestMine(mines);

	//normalise it
	Vec2DNormalize(vClosestMine);

	//add in vector to closest mine
	brain.inputs[0] = vClosestMine.x;
	brain.inputs[1] = vClosestMine.y;

	//add in sweepers look at vector
	brain.inputs[2] = m_vLookAt.x;
	brain.inputs[3] = m_vLookAt.y;

	//update the brain
	brain.calculate();

	//assign the outputs to the sweepers left & right tracks
	m_lTrack = brain.outputs[0];
	m_rTrack = brain.outputs[1];

	//calculate steering forces
	double RotForce = m_lTrack - m_rTrack;

	//clamp rotation
	Clamp(RotForce, -pParams->dMaxTurnRate, pParams->dMaxTurnRate);

	m_dRotation += RotForce;

	m_dSpeed = (m_lTrack + m_rTrack);	

	//update Look At 
	m_vLookAt.x = -sin(m_dRotation);
	m_vLookAt.y = cos(m_dRotation);

	//update position
	m_vPosition += (m_vLookAt * m_dSpeed);

	//wrap around window limits
	if (m_vPosition.x > pParams->WindowWidth) m_vPosition.x = 0;
	if (m_vPosition.x < 0) m_vPosition.x = pParams->WindowWidth;
	if (m_vPosition.y > pParams->WindowHeight) m_vPosition.y = 0;
	if (m_vPosition.y < 0) m_vPosition.y = pParams->WindowHeight;

	return true;
}


//----------------------GetClosestObject()---------------------------------
//
//	returns the vector from the sweeper to the closest mine
//
//-----------------------------------------------------------------------
SVector2D CMineSweeper::GetClosestMine(vector<SVector2D> &mines)
{
	double			closest_so_far = 99999;
	SVector2D		vClosestObject(0, 0);

	//cycle through mines to find closest
	for (vector<SVector2D>::size_type i = 0; i < mines.size(); i++)
	{
		double len_to_object = Vec2DLength(mines[i] - m_vPosition);

		if (len_to_object < closest_so_far)
		{
			closest_so_far	= len_to_object;

			vClosestObject	= m_vPosition - mines[i];

			m_iClosestMine  = i;
		}
	}

	return vClosestObject;
}

//----------------------------- CheckForMine -----------------------------
//
//  this function checks for collision with its closest mine (calculated
//  earlier and stored in m_iClosestMine)
//-----------------------------------------------------------------------
int CMineSweeper::CheckForMine(vector<SVector2D> &mines, double size)
{
	SVector2D DistToObject = m_vPosition - mines[m_iClosestMine];

	if (Vec2DLength(DistToObject) < (size + 5))
	{
		return m_iClosestMine;
	}

	return -1;
}