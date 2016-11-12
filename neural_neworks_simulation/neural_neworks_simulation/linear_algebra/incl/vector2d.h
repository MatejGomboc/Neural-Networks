#pragma once


class Vector2D
{
public:
	double m_dX;
	double m_dY;

	Vector2D(const double x = 0.0, const double y = 0.0);

	Vector2D& operator+=(const Vector2D& rhs);
	Vector2D& operator-=(const Vector2D& rhs);
	Vector2D& operator*=(const double& rhs);
	Vector2D& operator/=(const double& rhs);

	// returns the length of a 2D vector
	double length(void);

	// normalizes a 2D Vector
	void normalize(void);

	// calculates the dot product
	static double dot(const Vector2D& v1, const Vector2D& v2);

	// returns positive if v2 is clockwise of v1, minus if anticlockwise
	static double sign(const Vector2D& v1, const Vector2D& v2);
};


extern Vector2D operator*(const Vector2D& lhs, const double rhs);
extern Vector2D operator*(const double lhs, const Vector2D& rhs);
extern Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);