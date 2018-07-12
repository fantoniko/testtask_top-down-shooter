#pragma once
#include "SDL.h"
#include "ActiveObject.h"

enum CompassVectorDirection
{
	COMPASS_NORTHEAST,
	COMPASS_NORTHWEST,
	COMPASS_SOUTHWEST,
	COMPASS_SOUTHEAST
};

class Bullet : ActiveObject 
{
	static const int BULLET_BOX_SIZE;
	static const int BULLET_MOVE_STEP;
	static const double LINE_STEP_FOR_BULLET_CIRCLE;

	static SDL_Rect screenRect;

private:
	void ReflectDirection(SDL_Rect wall);
	CompassVectorDirection GetCompassDirection();

public:
	Bullet();
	Bullet(const SDL_Point& start, const Vector2D& direction);
	~Bullet();
	void Move(const std::vector<SDL_Rect>& map);
	void Show(SDL_Renderer* renderer);
	SDL_Rect GetRect();
};

