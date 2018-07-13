#pragma once
#include "SDL.h"

//	Класс контроля FPS, отображения готовой сцены и очистки экрана
class FPS_Control
{
	//	Ограничение на макс. кол-во FPS
	static const int FPS_LOCK = 60;
	//	Указатель на Renderer для использумего окна
	static SDL_Renderer* renderer;
	//	Тик программы в начале игрового цикла
	Uint32 startTimeOfFrame;

public:
	FPS_Control(SDL_Renderer* renderer);
	~FPS_Control();
};

