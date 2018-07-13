#pragma once
#include "Player.h"
#include <ctime>

class BotPlayer : public Player
{	
	int botUpdateChecker;
	bool noObstaclesBetween;

public:
	BotPlayer();
	~BotPlayer();

	bool UpdateChecker(int limit);
	void Update(const std::vector<SDL_Rect>& map, std::vector<Bullet>& bullets, const SDL_Rect playerRect);
};
