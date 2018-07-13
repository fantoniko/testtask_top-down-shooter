#include "ActiveObject.h"

ActiveObject::ActiveObject() {}

void ActiveObject::DrawCircle(SDL_Renderer* renderer, const SDL_Rect& rectBorder, double lineStep)
{
	int radius = (rectBorder.w < rectBorder.h) ? rectBorder.w / 2 : rectBorder.h / 2;

	int x1 = rectBorder.x + rectBorder.w;
	int y1 = rectBorder.y + rectBorder.h / 2;
	int x2, y2;

	for (double i = 0; i < 3.14 * 2 + lineStep; i += lineStep)
	{
		x2 = int(cos(i) * radius + rectBorder.x + rectBorder.w / 2);
		y2 = int(sin(i) * radius + rectBorder.y + rectBorder.h / 2);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
	}
}

bool ActiveObject::Collision(const SDL_Rect& addRect)
{
	//4 проверки на явное отсутствие коллизии
	if (rect.y >= addRect.y + addRect.h)
		return 0;
	if (rect.x >= addRect.x + addRect.w)
		return 0;
	if (rect.y + rect.h <= addRect.y)
		return 0;
	if (rect.x + rect.w <= addRect.x)
		return 0;
	return 1;
}

const SDL_Rect& ActiveObject::GetRect()
{
	return rect;
}
