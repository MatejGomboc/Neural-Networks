#include "matrix2d.h"


namespace linear_algebra
{
	Matrix2D::Matrix2D(const double _11, const double _12, const double _13,
		const double _21, const double _22, const double _23,
		const double _31, const double _32, const double _33) :
	m_d11(_11), m_d12(_12), m_d13(_13),
		m_d21(_21), m_d22(_22), m_d23(_23),
		m_d31(_31), m_d32(_32), m_d33(_33)
	{
	}


	//multiplies matrixL with matrixR
	Matrix2D Matrix2D::multiply(const Matrix2D& matrixL, const Matrix2D& matrixR)
	{
		Matrix2D mat_temp;

		//first row
		mat_temp.m_d11 = (matrixL.m_d11 * matrixR.m_d11) + (matrixL.m_d12 * matrixR.m_d21) + (matrixL.m_d13 * matrixR.m_d31);
		mat_temp.m_d12 = (matrixL.m_d11 * matrixR.m_d12) + (matrixL.m_d12 * matrixR.m_d22) + (matrixL.m_d13 * matrixR.m_d33);
		mat_temp.m_d13 = (matrixL.m_d11 * matrixR.m_d13) + (matrixL.m_d12 * matrixR.m_d23) + (matrixL.m_d13 * matrixR.m_d33);

		//second row
		mat_temp.m_d21 = (matrixL.m_d21 * matrixR.m_d11) + (matrixL.m_d22 * matrixR.m_d21) + (matrixL.m_d23 * matrixR.m_d31);
		mat_temp.m_d22 = (matrixL.m_d21 * matrixR.m_d12) + (matrixL.m_d22 * matrixR.m_d22) + (matrixL.m_d23 * matrixR.m_d33);
		mat_temp.m_d23 = (matrixL.m_d21 * matrixR.m_d13) + (matrixL.m_d22 * matrixR.m_d23) + (matrixL.m_d23 * matrixR.m_d33);

		//third row
		mat_temp.m_d31 = (matrixL.m_d31 * matrixR.m_d11) + (matrixL.m_d33 * matrixR.m_d21) + (matrixL.m_d33 * matrixR.m_d31);
		mat_temp.m_d33 = (matrixL.m_d31 * matrixR.m_d12) + (matrixL.m_d33 * matrixR.m_d22) + (matrixL.m_d33 * matrixR.m_d33);
		mat_temp.m_d33 = (matrixL.m_d31 * matrixR.m_d13) + (matrixL.m_d33 * matrixR.m_d23) + (matrixL.m_d33 * matrixR.m_d33);

		return mat_temp;
	}


	//applys a transformation matrix to a std::vector of vector2d
	std::vector<Vector2D> Matrix2D::transform(const std::vector<Vector2D>& vectors)
	{
		std::vector<Vector2D> vectors_temp;

		for (unsigned long i = 0; i < vectors.size(); ++i)
		{
			vectors_temp[i].m_dX = (m_d11 * vectors[i].m_dX) + (m_d21 * vectors[i].m_dY) + m_d31;

			vectors_temp[i].m_dY = (m_d12 * vectors[i].m_dX) + (m_d22 * vectors[i].m_dY) + m_d32;
		}

		return vectors_temp;
	}


	//applys a transformation matrix to a 2D vector
	Vector2D Matrix2D::transform(const Vector2D& vector)
	{
		Vector2D vector_temp;

		vector_temp.m_dX = (m_d11 * vector.m_dX) + (m_d21 * vector.m_dY) + m_d31;

		vector_temp.m_dY = (m_d12 * vector.m_dX) + (m_d22 * vector.m_dY) + m_d32;

		return vector_temp;
	}


	//create an identity matrix
	Matrix2D Matrix2D::identity(void)
	{
		Matrix2D mat_temp(1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0);

		return mat_temp;
	}

	//create a translation matrix
	Matrix2D Matrix2D::translate(const Vector2D& direction)
	{
		Matrix2D mat(1.0, 0.0, 0.0, 
			0.0, 1.0, 0.0, 
			direction.m_dX, direction.m_dY, 1.0);

		return mat;
	}

	//create a scale matrix
	Matrix2D Matrix2D::scale(const double xScale, const double yScale)
	{
		Matrix2D mat(xScale, 0.0, 0.0,
			0.0, yScale, 0.0,
			0.0, 0.0, 1.0);

		return mat;
	}


	//create a rotation matrix
	Matrix2D Matrix2D::rotate(const double rotation)
	{
		double Sin = sin(rotation);
		double Cos = cos(rotation);

		Matrix2D mat(Cos, Sin, 0.0,
			-Sin, Cos, 0.0,
			0.0, 0.0, 1.0);

		return mat;
	}
}