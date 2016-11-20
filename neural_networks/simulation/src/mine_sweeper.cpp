#include "mine_sweeper.h"
#include <vector>
#include <cmath>
#include "utils.h"
#include "matrix2d.h"
#include "vector2d.h"
#include "ini_params.h"
#include "mine.h"
#include "rand_gen.h"
#include "member.h"
#include "nn_util.h"

using namespace Linear_algebra;
using namespace Neural_networks;


namespace Simulation
{
	//-----------------------------------constructor-------------------------
	//-----------------------------------------------------------------------
	Mine_sweeper::Mine_sweeper(const unsigned long N_neurons) :
		m_vPosition(Vector2D(random_double(0.0, 1.0), random_double(0.0, 1.0))),
		m_dRotation(random_double(0.0, 1.0)),
		m_dSpeed(random_double(0.0, 1.0)),
		m_ulScore(0),
		m_ulClosestMine(0),
		Member(2, N_neurons, 2)
	{
	}


	//-------------------------------------------reset()--------------------
	//
	//	Resets the sweeper's position, score and rotation.
	//
	//----------------------------------------------------------------------
	void Mine_sweeper::reset()
	{
		Member::reset();

		//reset the sweepers positions
		m_vPosition = Vector2D(random_double(0.0, 1.0), random_double(0.0, 1.0));

		//and the score
		m_ulScore = 0;

		//and the rotation
		m_dRotation = random_double(0.0, 1.0);

		//and the speed
		m_dSpeed = random_double(0.0, 1.0);
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
	void Mine_sweeper::update(const std::vector<Mine>& mines, const Ini_params& params)
	{
		//get vector to the closest mine
		Vector2D vClosestMine = getClosestMine(mines);

		//normalize it
		vClosestMine.normalize();

		//add in vector to the closest mine
		Member::m_brain.m_dInputs[0] = vClosestMine.m_dX;
		Member::m_brain.m_dInputs[1] = vClosestMine.m_dY;

		//update the brain
		Member::m_brain.calculate();

		//get the outputs
		m_dSpeed = Member::m_brain.m_dOutputs[0] * params.m_dMaxSpeed;
		m_dRotation = Member::m_brain.m_dOutputs[1] * params.m_dTwoPi;

		//calculate vector of translation
		Vector2D translation(m_dSpeed * cos(m_dRotation), m_dSpeed * sin(m_dRotation));

		//update position
		m_vPosition += translation;

		//wrap around window limits
		m_vPosition.m_dX = Util::wrap(m_vPosition.m_dX, 0.0, 1.0);
		m_vPosition.m_dY = Util::wrap(m_vPosition.m_dY, 0.0, 1.0);
	}


	//----------------------getClosestMine()---------------------------------
	//
	//	returns the vector from the sweeper to the closest mine
	//
	//-----------------------------------------------------------------------
	Vector2D Mine_sweeper::getClosestMine(const std::vector<Mine>& mines)
	{
		double closest_so_far;
		Vector2D vClosestObject(0.0, 0.0);
		double len_to_object;

		//cycle through mines to find closest
		for (unsigned long i = 0; i < mines.size(); i++)
		{
			len_to_object = (mines[i].m_vPosition - m_vPosition).length();

			if ((len_to_object < closest_so_far) || (i == 0))
			{
				closest_so_far	= len_to_object;

				vClosestObject	= m_vPosition - mines[i].m_vPosition;

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
	void Mine_sweeper::checkCollision(std::vector<Mine>& mines, const double mine_size)
	{
		Vector2D distToObject = m_vPosition - mines[m_ulClosestMine].m_vPosition;

		if (distToObject.length() < mine_size)
		{
			//we have discovered a mine so increase score
			m_ulScore++;

			//replace the mine with another at a random position
			mines[m_ulClosestMine].reset();
		}
	}
}