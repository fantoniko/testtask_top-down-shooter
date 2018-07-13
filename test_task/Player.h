#pragma once
#include "ActiveObject.h"
#include "Bullet.h"

enum TurnPlayer
{
	TURN_CLOCKWISE,
	TURN_COUNTERCLOCKWISE
};

enum MoveDirection
{
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
};

class Player : public ActiveObject
{
protected:
	static const int PLAYER_BOX_SIZE;
	static const double DELTA_TURN;
	static const int PLAYER_MOVE_STEP;
	static const double LINE_STEP_FOR_PLAYER_CIRCLE;
	static const int FIRE_CALLDOWN_MS;

	Vector2D speedVector;
	SDL_Point playerCursor;
	Uint32 fireStart;

public:
	Player();
	Player(SDL_Point coords);
	~Player();
	void TurnSight(TurnPlayer turnPlayer);
	void Show(SDL_Renderer* renderer, bool showPlayerHitBoxes);
	void Move(const std::vector<SDL_Rect>& map, MoveDirection moveDirection);
	void Fire(std::vector<Bullet>& bullets);
	void SetPosition(const SDL_Point& coords);
};
