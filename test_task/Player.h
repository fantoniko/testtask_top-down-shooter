#pragma once
#include "SDL.h"
#include "ActiveObject.h"

class Player : public ActiveObject
{
	const int PLAYER_BOX_SIZE	= 50;
	const double DELTA_TURN		= 0.1;

public:
	Player();
	~Player();
	void TurnSight(TurnPlayer turn);
	void Show(SDL_Renderer* renderer);
};
