#pragma once
#include <SDL.h>

//	Класс обработчика событий клавиатуры
class KeyboardHandler
{
private:
	//	Массив всех клавиш
	Uint8* keyArray;
	//	SDL_Событие
	SDL_Event event;

public:
	//	Обновление состояний клавиш
	void UpdateKeyStates();
	//	Проверка на нажатие
	bool IsKeyTapped(SDL_Scancode key);
	//	Проверка на нажатость клавиши
	bool IsKeyDown(SDL_Scancode key);
	//	Получение SDL-события
	SDL_Event GetEvent();
};