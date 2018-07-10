#pragma once
#include <cmath>
#include <vector>
#include "Windows.h"
#include "SDL.h"
#include "FPS_Control.h"
#include "Player.h"

class Game
{
	static const int SCREEN_WIDTH	= 900;
	static const int SCREEN_HEIGHT	= 600;
	static const int FPS			= 60;

	SDL_Window* mainWindow;
	SDL_Renderer* renderer;
	HDC hDC;

	bool running;
	std::vector<SDL_Rect> walls;
	Player mainPlayer;


public:
	Game();
	~Game();

	void Start();
	void UpdateScreen();

};

