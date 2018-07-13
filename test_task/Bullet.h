#pragma once
#include "SDL.h"
#include "ActiveObject.h"

//	Перечисление диагональных направлений по названиям сторон света
enum CompassVectorDirection
{
	COMPASS_NORTHEAST,
	COMPASS_NORTHWEST,
	COMPASS_SOUTHWEST,
	COMPASS_SOUTHEAST
};

//	Класс пули
class Bullet : ActiveObject 
{
	//	Размер хитбокса пули
	static const int BULLET_BOX_SIZE;
	//	Шаг движения пули
	static const int BULLET_MOVE_STEP;
	//	Шаг детализации модели пули
	static const double BULLET_CIRCLE_LINE_STEP;

private:
	//	Отражение траектории от стены
	void ReflectDirection(SDL_Rect wall);
	//	Получение направления вектора по подобию сторон света
	CompassVectorDirection GetCompassDirection();

public:
	//	Конструктор с начальной точкой появления и направлением движения
	Bullet(const SDL_Point& start, const Vector2D& direction);

	//	Движение с проверкой на коллизии со стенами
	void Move(const std::vector<SDL_Rect>& map);
	//	Отображение на экран
	void Show(SDL_Renderer* renderer, bool showHitBoxes);
	//	Получение координат хитбокса
	SDL_Rect GetRect();
};

