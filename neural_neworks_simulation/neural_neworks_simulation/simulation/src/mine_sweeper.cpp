#include "mine_sweeper.h"


//-----------------------------------constructor-------------------------
//-----------------------------------------------------------------------
Mine_sweeper::Mine_sweeper() :
	Member(2,2,2),
	m_vPosition(Vector2D(0.0, 0.0)),
	m_dRotation(0.0),
	m_dSpeed(0.0),
	m_dScore(0.0)
{
}


//-------------------------------------------Reset()--------------------
//
//	Resets the sweeper's position, core and rotation.
//
//----------------------------------------------------------------------
void Mine_sweeper::reset()
{
	//reset the sweepers positions
	m_vPosition = Vector2D(0.0, 0.0);

	//and the score
	m_dScore = 0.0;

	//and the rotation
	m_dRotation = 0.0;

	//and the speed
	m_dSpeed = 0.0;
}


//---------------------WorldTransform--------------------------------
//
//	Sets up a transformation matrix for the sweeper's position vector,
//  according to its current scale, rotation and position, and transforms
//  it.
//
//-------------------------------------------------------------------
void Mine_sweeper::worldTransform(void)
{
	//create the world transformation matrix
	Matrix2D matrix = Matrix2D::identity();

	//scale
	matrix = Matrix2D::multiply(matrix, Matrix2D::scale(1.0, 1.0)); //TODO!!

	//rotate
	matrix = Matrix2D::multiply(matrix, Matrix2D::rotate(m_dRotation));

	//and translate
	matrix = Matrix2D::multiply(matrix, Matrix2D::translate(m_vPosition));

	//now transform the position vector
	m_vPosition = matrix.transform(m_vPosition);
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
void Mine_sweeper::update(const std::vector<Vector2D>& mines)
{
	//get vector to closest mine
	Vector2D vClosestMine = GetClosestMine(mines);

	//normalise it
	vClosestMine.normalize();

	//add in vector to closest mine
	inputs.push_back(vClosestMine.x);
	inputs.push_back(vClosestMine.y);

	//add in sweepers look at vector
	inputs.push_back(m_vLookAt.x);
	inputs.push_back(m_vLookAt.y);


	//update the brain and get feedback
	vector<double> output = m_ItsBrain.Update(inputs);

	//make sure there were no errors in calculating the 
	//output
	if (output.size() < CParams::iNumOutputs) 
	{
		return false;
	}

	//assign the outputs to the sweepers left & right tracks
	m_lTrack = output[0];
	m_rTrack = output[1];

	//calculate steering forces
	double RotForce = m_lTrack - m_rTrack;

	//clamp rotation
	Clamp(RotForce, -CParams::dMaxTurnRate, CParams::dMaxTurnRate);

	m_dRotation += RotForce;

	m_dSpeed = (m_lTrack + m_rTrack);	

	//update Look At 
	m_vLookAt.x = -sin(m_dRotation);
	m_vLookAt.y = cos(m_dRotation);

	//update position
	m_vPosition += (m_vLookAt * m_dSpeed);

	//wrap around window limits
	if (m_vPosition.x > CParams::WindowWidth) m_vPosition.x = 0;
	if (m_vPosition.x < 0) m_vPosition.x = CParams::WindowWidth;
	if (m_vPosition.y > CParams::WindowHeight) m_vPosition.y = 0;
	if (m_vPosition.y < 0) m_vPosition.y = CParams::WindowHeight;

	return true;
}


//----------------------GetClosestObject()---------------------------------
//
//	returns the vector from the sweeper to the closest mine
//
//-----------------------------------------------------------------------
SVector2D CMinesweeper::GetClosestMine(vector<SVector2D> &mines)
{
	double			closest_so_far = 99999;

	SVector2D		vClosestObject(0, 0);

	//cycle through mines to find closest
	for (int i=0; i<mines.size(); i++)
	{
		double len_to_object = Vec2DLength(mines[i] - m_vPosition);

		if (len_to_object < closest_so_far)
		{
			closest_so_far	= len_to_object;

			vClosestObject	= m_vPosition - mines[i];

			m_iClosestMine = i;
		}
	}

	return vClosestObject;
}
//----------------------------- CheckForMine -----------------------------
//
//  this function checks for collision with its closest mine (calculated
//  earlier and stored in m_iClosestMine)
//-----------------------------------------------------------------------
int CMinesweeper::CheckForMine(vector<SVector2D> &mines, double size)
{
	SVector2D DistToObject = m_vPosition - mines[m_iClosestMine];

	if (Vec2DLength(DistToObject) < (size + 5))
	{
		return m_iClosestMine;
	}

	return -1;
}


