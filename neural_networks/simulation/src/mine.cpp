#include "mine.h"
#include "vector2d.h"
#include "matrix2d.h"
#include "rand_gen.h"

using namespace Linear_algebra;
using namespace Neural_networks;

namespace Simulation
{
	 Mine::Mine(void) :
		m_vPosition(random_double(0.0, 1.0), random_double(0.0, 1.0))
	 {
	 }


	 void Mine::reset(void)
	 {
		 m_vPosition = Vector2D(random_double(0.0, 1.0), random_double(0.0, 1.0));
	 }
}