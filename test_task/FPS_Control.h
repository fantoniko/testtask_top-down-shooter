#pragma once
#include "SDL.h"

class FPS_Control
{
	const int FPS_Lock = 60;
	Uint32 startTimeOfFrame;
	static SDL_Renderer* renderer;

public:
	FPS_Control(SDL_Renderer* renderer);
	~FPS_Control();
};

