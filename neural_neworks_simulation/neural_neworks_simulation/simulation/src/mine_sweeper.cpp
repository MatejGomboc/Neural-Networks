#include "mine_sweeper.h"
#include <vector>
#include <cmath>

#include "utils.h"
#include "matrix2d.h"
#include "vector2d.h"
#include "ini_params.h"

using namespace linear_algebra;


//-----------------------------------constructor-------------------------
//-----------------------------------------------------------------------
Mine_sweeper::Mine_sweeper() :
	m_vPosition(Vector2D(0.0, 0.0)),
	m_dRotation(0.0),
	m_dSpeed(0.0),
	m_dScore(0.0),
	m_ulClosestMine(0)
{
}


//-------------------------------------------reset()--------------------
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


//---------------------worldTransform--------------------------------
//
//	Sets up a transformation matrix for the sweeper's position vector,
//  according to its current scale, rotation and position, and transforms
//  it.
//
//-------------------------------------------------------------------
void Mine_sweeper::worldTransform(const double sweeper_scale)
{
	//create the world transformation matrix
	Matrix2D matrix = Matrix2D::identity();

	//scale
	matrix = Matrix2D::multiply(matrix, Matrix2D::scale(sweeper_scale, sweeper_scale));

	//rotate
	matrix = Matrix2D::multiply(matrix, Matrix2D::rotate(m_dRotation));

	//and translate
	matrix = Matrix2D::multiply(matrix, Matrix2D::translate(m_vPosition));

	//now transform the position vector
	m_vPosition = matrix.transform(m_vPosition);
}


//-------------------------------update()--------------------------------
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
	Vector2D vClosestMine = getClosestMine(mines);

	//normalise it
	vClosestMine.normalize();

	////add in vector to closest mine

	////add in sweepers look at vector

	//update the brain and get feedback

	//assign the outputs to the sweepers left & right tracks

	//calculate steering forces

	//clamp rotation

	//update Look At 

	//update position

	//wrap around window limits
}


//----------------------getClosestMine()---------------------------------
//
//	returns the vector from the sweeper to the closest mine
//
//-----------------------------------------------------------------------
Vector2D Mine_sweeper::getClosestMine(const std::vector<Vector2D>& mines)
{
	double closest_so_far;
	Vector2D vClosestObject(0.0, 0.0);
	double len_to_object;

	//cycle through mines to find closest
	for (unsigned long i = 0; i < mines.size(); i++)
	{
		len_to_object = (mines[i] - m_vPosition).length();

		if ((len_to_object < closest_so_far) || (i == 0))
		{
			closest_so_far	= len_to_object;

			vClosestObject	= m_vPosition - mines[i];

			m_ulClosestMine = i;
		}
	}

	return vClosestObject;
}


//-----------------------------checkCollision----------------------------
//
//  this function checks for collision with its closest mine (calculated
//  earlier and stored in m_iClosestMine)
//-----------------------------------------------------------------------
bool Mine_sweeper::checkCollision(const std::vector<Vector2D> &mines, const double mine_size)
{
	Vector2D distToObject = m_vPosition - mines[m_ulClosestMine];

	if (distToObject.length() < mine_size) return true;
	else return false;
}


