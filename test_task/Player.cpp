#include "Player.h"

const int Player::PLAYER_BOX_SIZE					= 40;
const double Player::DELTA_TURN						= 0.1;
const int Player::PLAYER_MOVE_STEP					= 5;
const double Player::LINE_STEP_FOR_PLAYER_CIRCLE	= 0.05;

Player::Player()
{
	direction.x = 0;
	direction.y = 1;
	rect = { 500, 300, PLAYER_BOX_SIZE, PLAYER_BOX_SIZE };
}

Player::~Player()
{
}

void Player::TurnSight(TurnPlayer turnPlayer)
{
	double tempX, tempY;
	if (turnPlayer == TURN_CLOCKWISE)
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

void Player::Move(const std::vector<SDL_Rect>& map, MoveDirection moveDirection)
{
	SDL_Rect tempRect = rect;
	switch (moveDirection)
	{
	case MOVE_FORWARD:
		rect.x += direction.x * PLAYER_MOVE_STEP;
		rect.y += direction.y * PLAYER_MOVE_STEP;
		break;
	case MOVE_BACKWARD:
		rect.x -= direction.x * PLAYER_MOVE_STEP;
		rect.y -= direction.y * PLAYER_MOVE_STEP;
		break;
	case MOVE_LEFT:
		rect.x += direction.y * PLAYER_MOVE_STEP;
		rect.y -= direction.x * PLAYER_MOVE_STEP;
		break;
	case MOVE_RIGHT:
		rect.x -= direction.y * PLAYER_MOVE_STEP;
		rect.y += direction.x * PLAYER_MOVE_STEP;
		break;
	}

	for (auto i = 0; i < map.size(); i++)
	{
		if (Collision(map[i]))
		{
			rect = tempRect;
			return;
		}		
	}
}

void Player::Fire(std::vector<Bullet>& bullets)
{
	bullets.push_back(Bullet(playerCursor, direction));
}

void Player::SetPosition(SDL_Point coords)
{
	rect = { coords.x, coords.y, PLAYER_BOX_SIZE, PLAYER_BOX_SIZE };
	direction.x = 0;
	direction.y = 1;
}

void Player::Show(SDL_Renderer* renderer, bool showHitBoxes)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
	DrawCircle(renderer, rect, LINE_STEP_FOR_PLAYER_CIRCLE);
	int centerX = rect.x + rect.w / 2;
	int centerY = rect.y + rect.h / 2;
	playerCursor.x = centerX + direction.x * PLAYER_BOX_SIZE / 1.2;
	playerCursor.y = centerY + direction.y * PLAYER_BOX_SIZE / 1.2;

	SDL_RenderDrawLine(renderer, centerX, centerY, playerCursor.x, playerCursor.y);

	if(showHitBoxes)
		SDL_RenderDrawRect(renderer, &rect);
}