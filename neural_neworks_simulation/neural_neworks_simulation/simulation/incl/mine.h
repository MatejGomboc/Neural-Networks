#pragma once

#include "vector2d.h"


namespace Simulation
{
	class Mine
	{
	public:
		Linear_algebra::Vector2D m_vPosition;

		Mine(void);

		void reset(void);
	};
};