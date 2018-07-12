#pragma once
#include <cmath>
#include <vector>
#include "Windows.h"
#include "SDL.h"
#include "KeyboardHandler.h"
#include "FPS_Control.h"
#include "Player.h"

class Game : ActiveObject
{
	static const int SCREEN_WIDTH	= 900;
	static const int SCREEN_HEIGHT	= 600;
	static const int FPS			= 60;

	SDL_Window* mainWindow;
	SDL_Renderer* renderer;

	bool running;
	bool showHitBoxes;
	KeyboardHandler keyHandler;
	Player mainPlayer;
	std::vector<SDL_Rect> map;
	std::vector<Bullet> bullets;

private:
	void EventHandler();
	void LogicUpdater();
	void ScreenUpdater();

public:
	Game();
	~Game();

	void Start();
};

