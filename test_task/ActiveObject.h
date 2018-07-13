#pragma once
#include "SDL.h"
#include <vector>
#include "Vector2D.h"

// Абстрактный класс для наследования движущимися объектами
class ActiveObject abstract 
{
protected: 
	Vector2D direction; // Вектор направления движения
	SDL_Rect rect;		// Прямоуголная область, принадлежащая объекту 
	
public:
	ActiveObject();

	// Метод для рисования круга
	void DrawCircle(SDL_Renderer* renderer, const SDL_Rect& rectBorder, double lineStep); 
	// Метод проверки пересечения с другим объектом
	bool Collision(const SDL_Rect& addRect);
	// Метод получения прямоугольной области объекта
	const SDL_Rect& GetRect();
};

