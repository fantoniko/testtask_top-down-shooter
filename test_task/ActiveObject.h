#pragma once
#include "SDL.h"

struct Vector2D
{
	double x;
	double y;
};

enum TurnPlayer
{
	CLOCKWISE,
	COUNTERCLOCKWISE
};

class ActiveObject abstract
{
protected: 
	Vector2D direction;
	SDL_Rect rect;
public:
	ActiveObject();
	~ActiveObject();

	void DrawCircle(SDL_Renderer* renderer, const SDL_Rect& rect);
	bool Collision(const SDL_Rect& rect1, const SDL_Rect& rect2);
};

