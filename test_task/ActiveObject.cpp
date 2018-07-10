#include "ActiveObject.h"



ActiveObject::ActiveObject()
{
	direction.x = 0;
	direction.y = 1;
}


ActiveObject::~ActiveObject()
{
}

void ActiveObject::DrawCircle(SDL_Renderer* renderer, const SDL_Rect& rect)
{
	int radius = (rect.w < rect.h) ? rect.w / 2 : rect.h / 2;

	int x1 = rect.x + rect.w;
	int y1 = rect.y + rect.h / 2;
	int x2, y2;
	for (double i = 0; i < 3.14 * 2; i += 0.05)
	{
		x2 = cos(i) * radius + rect.x + rect.w / 2;
		y2 = sin(i) * radius + rect.y + rect.h / 2;
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
	}
	//SDL_RenderDrawRect(renderer, &rect);
}

bool ActiveObject::Collision(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
	if (rect1.y >= rect2.y + rect2.h)
		return 0;
	if (rect1.x >= rect2.x + rect2.w)
		return 0;
	if (rect1.y + rect1.h <= rect2.y)
		return 0;
	if (rect1.x + rect1.w <= rect2.x)
		return 0;
	return 1;
}