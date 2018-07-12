#pragma once
#include "SDL.h"
#include <vector>
#include "Vector2D.h"


class ActiveObject abstract
{
protected: 
	Vector2D direction;
	SDL_Rect rect;
	
public:
	ActiveObject();
	~ActiveObject();

	void DrawCircle(SDL_Renderer* renderer, const SDL_Rect& rectBorder, double lineStep);
	bool Collision(const SDL_Rect& addRect);
};

