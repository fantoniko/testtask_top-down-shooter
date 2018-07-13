#pragma once
#include <cmath>
#include <vector>
#include <string>
#include "Windows.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "KeyboardHandler.h"
#include "FPS_Control.h"
#include "BotPlayer.h"

struct GameScore
{
	int playerPoints;
	int botPoints;
};

class Game : ActiveObject
{
	static const int SCREEN_WIDTH	= 900;
	static const int SCREEN_HEIGHT	= 600;
	static const int FPS			= 60;

	SDL_Window* mainWindow;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* scoreTexture;
	SDL_Rect scoreRect;

	bool running;
	bool roundContinues;
	bool showHitBoxes;
	KeyboardHandler keyHandler;
	Player mainPlayer;
	BotPlayer botPlayer;
	std::vector<SDL_Rect> map;
	std::vector<Bullet> bullets;
	GameScore score;

private:
	void EventHandler();
	void LogicUpdater();
	void ScreenUpdater();
	void Restart(bool playerWins);

public:
	Game();
	~Game();

	void Start();
};

