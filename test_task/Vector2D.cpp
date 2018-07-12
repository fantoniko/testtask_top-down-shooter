#include "Vector2D.h"



Vector2D::Vector2D()
{
}


Vector2D::~Vector2D()
{
}

Vector2D Vector2D::Normalize()
{
	double length = sqrt(x * x + y * y);
	*this = *this / length;
	return *this;
}

Vector2D Vector2D::operator+(Vector2D addVector)
{
	return Vector2D(x + addVector.x, y + addVector.y);
}

Vector2D Vector2D::operator-(Vector2D addVector)
{
	return Vector2D(x - addVector.x, y - addVector.y);
}

Vector2D Vector2D::operator*(Vector2D addVector)
{
	return Vector2D(x * addVector.x, y * addVector.y);
}
