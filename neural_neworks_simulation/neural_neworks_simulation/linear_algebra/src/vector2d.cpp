#include "vector2d.h"
#include <cmath>


Vector2D::Vector2D(const double x, const double y) :
	m_dX(x),
	m_dY(y)
{
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
	m_dX += rhs.m_dX;
	m_dY += rhs.m_dY;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
	m_dX -= rhs.m_dX;
	m_dY -= rhs.m_dY;

	return *this;
}

Vector2D& Vector2D::operator*=(const double& rhs)
{
	m_dX *= rhs;
	m_dY *= rhs;

	return *this;
}

Vector2D& Vector2D::operator/=(const double& rhs)
{
	m_dX /= rhs;
	m_dY /= rhs;

	return *this;
}


Vector2D operator*(const Vector2D& lhs, const double rhs)
{
	Vector2D result(lhs);
	result *= rhs;
	return result;
}

Vector2D operator*(const double lhs, const Vector2D& rhs)
{
	Vector2D result(rhs);
	result *= lhs;
	return result;
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
	Vector2D result(lhs);
	result.m_dX -= rhs.m_dX;
	result.m_dY -= rhs.m_dY;

	return result;
}


//------------------------- Vec2DLength -----------------------------
//
//	returns the length of a 2D vector
//--------------------------------------------------------------------
double Vector2D::length(void)
{
	return sqrt(m_dX * m_dX + m_dY * m_dY);
}

//------------------------- Vec2DNormalize -----------------------------
//
//	normalizes a 2D Vector
//--------------------------------------------------------------------
void Vector2D::normalize(void)
{
	double vector_length = length();

	m_dX = m_dX / vector_length;
	m_dY = m_dY / vector_length;
}

//------------------------- Vec2DDot --------------------------
//
//	calculates the dot product
//--------------------------------------------------------------------
double dot(const Vector2D& v1, const Vector2D& v2)
{
	return v1.m_dX * v2.m_dX + v1.m_dY * v2.m_dY;
}

//------------------------ Vec2DSign --------------------------------
//
//  returns positive if v2 is clockwise of v1, minus if anticlockwise
//-------------------------------------------------------------------
double sign(const Vector2D& v1, const Vector2D& v2)
{
	if (v1.m_dY * v2.m_dX > v1.m_dX * v2.m_dY)
	{ 
		return 1.0;
	}
	else 
	{
		return -1.0;
	}
}