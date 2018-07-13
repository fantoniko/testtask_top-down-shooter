#include "Bullet.h"

const int Bullet::BULLET_BOX_SIZE					= 5;
const int Bullet::BULLET_MOVE_STEP					= 6;
const double Bullet::BULLET_CIRCLE_LINE_STEP		= 0.5;

Bullet::Bullet(const SDL_Point& start, const Vector2D& direction)
{
	this->direction = direction;
	rect = { start.x, start.y, BULLET_BOX_SIZE, BULLET_BOX_SIZE };
}

void Bullet::Move(const std::vector<SDL_Rect>& map)
{
	//	Изменение координат в соответствии с направлением и шагом
	rect.x += direction.x * BULLET_MOVE_STEP;
	rect.y += direction.y * BULLET_MOVE_STEP;

	//	Проверка на коллизии с последующим отражением
	for (auto i = 0; i < map.size(); i++)
	{
		if (Collision(map[i]))
			ReflectDirection(map[i]);
	}
}

void Bullet::Show(SDL_Renderer* renderer, bool showHitBoxes)
{
	//	Установка цвета и отрисовка круга для модели пули 
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	DrawCircle(renderer, rect, BULLET_CIRCLE_LINE_STEP);

	//	Доп. отображение хитбоксов пуль
	if (showHitBoxes)
		SDL_RenderDrawRect(renderer, &rect);
}

SDL_Rect Bullet::GetRect()
{
	return rect;
}

void Bullet::ReflectDirection(SDL_Rect wall)
{
	//	Коэффициент обратного смещения для лучшей работы детектора коллизии
	int offsetCoef = 4;
	//	Точки-концы вектора-отражателя
	SDL_Point point1, point2;

	//	Получение направления движения по сторонам света для последующего определения
	//	тех стен, с которыми могло произойти столковение
	CompassVectorDirection cvd = GetCompassDirection();
	switch (cvd)
	{
	//	Движение в направлении СЕВЕРО-ВОСТОКА => столкновение могло произойти 
	//	с НИЖНЕЙ либо ЛЕВОЙ плоскостью стены
	//	Определение нужной плоскости посредством сравнения глубины проникновения по x и y
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
		// Небольшое обратное по направлению движения смещение 
		// для избежания багов с застреванием пуль в стенах
		rect.x -= BULLET_MOVE_STEP / offsetCoef;
		rect.y += BULLET_MOVE_STEP / offsetCoef;
		break;

	//	Движение в направлении СЕВЕРО-ЗАПАДА => столкновение могло произойти 
	//	с НИЖНЕЙ либо ПРАВОЙ плоскостью стены
	//	-//-
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
		// -//-
		rect.x += BULLET_MOVE_STEP / offsetCoef;
		rect.y += BULLET_MOVE_STEP / offsetCoef;
		break;

		//	Движение в направлении ЮГО-ЗАПАДА => столкновение могло произойти 
		//	с ВЕРХНЕЙ либо ПРАВОЙ плоскостью стены
		//	-//-
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
		// -//-
		rect.x += BULLET_MOVE_STEP / offsetCoef;
		rect.y -= BULLET_MOVE_STEP / offsetCoef;
		break;

		//	Движение в направлении ЮГО-ВОСТОКА => столкновение могло произойти 
		//	с ВЕРХНЕЙ либо ЛЕВОЙ плоскостью стены
		//	-//-
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
		//	-//-
		rect.x -= BULLET_MOVE_STEP / offsetCoef;
		rect.y -= BULLET_MOVE_STEP / offsetCoef;
		break;

	default:
		break;
	}
	//	Получение вектора из найденных точек плоскости-отражателя
	Vector2D reflectiveSurface(point1, point2);
	//	Получение вектора-нормали к плоскости-отражателю
	Vector2D surfaceNormal(reflectiveSurface.y, -reflectiveSurface.x);
	//	Нормализация вектора
	surfaceNormal.Normalize();
	//	Получение отраженного вектора
	direction = direction - surfaceNormal * 2 * (direction * surfaceNormal);
}

CompassVectorDirection Bullet::GetCompassDirection()
{
	//Получение направления вектора в сторонах света по комбинации x и y
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
