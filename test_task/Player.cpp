#include "Player.h"

Player::Player()
{
	rect = { 500, 500, PLAYER_BOX_SIZE, PLAYER_BOX_SIZE };
}

Player::~Player()
{
}

void Player::TurnSight(TurnPlayer turn)
{
	double tempX, tempY;
	if (turn == CLOCKWISE)
	{
		tempX = direction.x * cos(DELTA_TURN) - direction.y * sin(DELTA_TURN);
		tempY = direction.x * sin(DELTA_TURN) + direction.y * cos(DELTA_TURN);
	}
	else
	{
		tempX = direction.x * cos(DELTA_TURN) + direction.y * sin(DELTA_TURN);
		tempY = -1 * direction.x * sin(DELTA_TURN) + direction.y * cos(DELTA_TURN);
	}

	direction.x = tempX;
	direction.y = tempY;
}

void Player::Show(SDL_Renderer* renderer)
{
	DrawCircle(renderer, rect);
	int centerX = rect.x + rect.w / 2;
	int centerY = rect.y + rect.h / 2;
	int finalX = centerX + direction.x * PLAYER_BOX_SIZE / 2;
	int	finalY = centerX + direction.y * PLAYER_BOX_SIZE / 2;
	SDL_RenderDrawLine(renderer, centerX, centerY, finalX, finalY);
}
