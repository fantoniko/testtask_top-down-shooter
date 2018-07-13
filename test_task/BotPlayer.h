#pragma once
#include "Player.h"
#include <ctime>

class BotPlayer : public Player
{
	const int fireCallDownMs = 300;
	
	Uint32 fireStart;
	int botUpdateChecker;
	bool noObstaclesBetween;
	SDL_TimerID fireTimer;

public:
	BotPlayer();
	BotPlayer(SDL_Point coords);
	~BotPlayer();

	bool UpdateChecker(int limit);
	void Update(const std::vector<SDL_Rect>& map, std::vector<Bullet>& bullets, const SDL_Rect playerRect);
};
