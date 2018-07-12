#include "Bullet.h"

const int Bullet::BULLET_BOX_SIZE					= 5;
const int Bullet::BULLET_MOVE_STEP					= 7;
const double Bullet::LINE_STEP_FOR_BULLET_CIRCLE	= 0.2;

Bullet::Bullet()
{
}

Bullet::Bullet(const SDL_Point& start, const Vector2D& direction)
{
	this->direction = direction;
	rect = { start.x, start.y, BULLET_BOX_SIZE, BULLET_BOX_SIZE };
}

Bullet::~Bullet()
{
}

void Bullet::Move(const std::vector<SDL_Rect>& map)
{
	rect.x += direction.x * BULLET_MOVE_STEP;
	rect.y += direction.y * BULLET_MOVE_STEP;

	for (auto i = map.begin(); i < map.end(); i++)
	{
		SDL_Rect wall = *i;
		if (Collision(wall))
			ReflectDirection(wall);
	}
}

void Bullet::Show(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	DrawCircle(renderer, rect, LINE_STEP_FOR_BULLET_CIRCLE);
}

SDL_Rect Bullet::GetRect()
{
	return rect;
}

void Bullet::ReflectDirection(SDL_Rect wall)
{
	SDL_Point point1, point2;
	CompassVectorDirection cvd = GetCompassDirection();
	switch (cvd)
	{
	case COMPASS_NORTHEAST:
		if (rect.x + rect.w - wall.x >= wall.y + wall.h - rect.y)
		{
			point1 = { wall.x, wall.y + wall.h };
			point2 = { wall.x + wall.w, wall.y + wall.h };
		}
		else 
		{
			point1 = { wall.x, wall.y};
			point2 = { wall.x, wall.y + wall.h };
		}
		break;
	case COMPASS_NORTHWEST:
		if (wall.x + wall.w - rect.x >= wall.y + wall.h - rect.y)
		{
			point1 = { wall.x, wall.y + wall.h };
			point2 = { wall.x + wall.w, wall.y + wall.h };
		}
		else
		{
			point1 = { wall.x + wall.w, wall.y + wall.h };
			point2 = { wall.x + wall.w, wall.y };
		}
		break;
	case COMPASS_SOUTHWEST:
		if (wall.x + wall.w - rect.x >= rect.y + rect.h - wall.y)
		{
			point1 = { wall.x + wall.w, wall.y };
			point2 = { wall.x, wall.y };
		}
		else
		{
			point1 = { wall.x + wall.w, wall.y + wall.h };
			point2 = { wall.x + wall.w, wall.y };
		}
		break;
	case COMPASS_SOUTHEAST:
		if (rect.x + rect.w - wall.x >= rect.y + rect.h - wall.y)
		{
			point1 = { wall.x + wall.w, wall.y };
			point2 = { wall.x, wall.y };
		}
		else
		{
			point1 = { wall.x, wall.y };
			point2 = { wall.x, wall.y + wall.h };
		}
		break;
	default:
		break;
	}

	Vector2D reflectiveSurface(point2, point1);
	Vector2D surfaceNormal(reflectiveSurface.y, -reflectiveSurface.x);
	surfaceNormal.Normalize();
	direction = direction + surfaceNormal * 2;
}

CompassVectorDirection Bullet::GetCompassDirection()
{
	if (direction.y >= 0)
	{
		if (direction.x >= 0)
			return COMPASS_SOUTHEAST;
		else
			return COMPASS_SOUTHWEST;
	}
	else
	{
		if (direction.x >= 0)
			return COMPASS_NORTHEAST;
		else
			return COMPASS_NORTHWEST;
	}
}
