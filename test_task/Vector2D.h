#pragma once
#include "SDL.h"

class Vector2D
{
public:
	double x;
	double y;

public:
	Vector2D();
	Vector2D(SDL_Point point1, SDL_Point point2) : x(point2.x - point1.x), y(point2.y - point1.y) {}
	Vector2D(double argX, double argY) : x(argX), y(argY) {}
	~Vector2D();

	Vector2D Normalize();
	Vector2D operator + (Vector2D addVector);
	template<typename T> Vector2D operator* (T coef);
	template<typename T> Vector2D operator/ (T divider);
};

template<typename T>
inline Vector2D Vector2D::operator* (T coef)
{
	return Vector2D(x * coef, y * coef);
}

template<typename T>
inline Vector2D Vector2D::operator/ (T divider)
{
	return Vector2D(x / divider, y / divider);
}
