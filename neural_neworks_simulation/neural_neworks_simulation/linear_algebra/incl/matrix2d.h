#pragma once

#include <cmath>
#include "vector2d.h"
#include <vector>


namespace linear_algebra
{
	class Matrix2D
	{
	public:
		double m_d11, m_d12, m_d13;
		double m_d21, m_d22, m_d23;
		double m_d31, m_d32, m_d33;

		Matrix2D(const double _11 = 0.0, const double _12 = 0.0, const double _13 = 0.0,
			const double _21 = 0.0, const double _22 = 0.0, const double _23 = 0.0,
			const double _31 = 0.0, const double _32 = 0.0, const double _33 = 0.0);

		//multiplies matrixL with matrixR
		static Matrix2D multiply(const Matrix2D& matrixL, const Matrix2D& matrixR);

		//create an identity matrix
		static Matrix2D identity();

		//create a translation matrix
		static Matrix2D translate(const Vector2D& direction);

		//create a scale matrix
		static Matrix2D scale(const double xScale, const double yScale);

		//create a rotation matrix
		static Matrix2D rotate(const double rotation);

		//applys a transformation matrix to a std::vector of vector2d
		std::vector<Vector2D> transform(const std::vector<Vector2D>& vectors);

		//applys a transformation matrix to a 2D vector
		Vector2D transform(const Vector2D& vector);
	};
}
