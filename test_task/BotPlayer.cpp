#include "BotPlayer.h"

BotPlayer::BotPlayer()
{
	direction.x = 0;
	direction.y = -1;
	rect = { 500, 300, PLAYER_BOX_SIZE, PLAYER_BOX_SIZE };
}

BotPlayer::~BotPlayer()
{
}

bool BotPlayer::UpdateChecker(int limit)
{
	botUpdateChecker++;
	if (botUpdateChecker >= limit)
	{
		botUpdateChecker = 0;
		return true;
	}
	return false;
}

void BotPlayer::Update(const std::vector<SDL_Rect>& map, std::vector<Bullet>& bullets, const SDL_Rect playerRect)
{
	SDL_Point centerBot = { rect.x + rect.w / 2, rect.y + rect.h / 2 };
	SDL_Point centerPlayer = { playerRect.x + playerRect.w / 2, playerRect.y + playerRect.h / 2 };
	direction = Vector2D(centerBot, centerPlayer).Normalize();

	srand(time(0));
	MoveDirection mDir = MoveDirection(rand() % 4);
	switch (mDir)
	{
	case MOVE_FORWARD:
		Move(map, MOVE_FORWARD);
		break;
	case MOVE_BACKWARD:
		Move(map, MOVE_BACKWARD);
		break;
	case MOVE_LEFT:
		Move(map, MOVE_LEFT);
		break;
	case MOVE_RIGHT:
		Move(map, MOVE_RIGHT);
		break;
	}

	noObstaclesBetween = true;
	for (auto i = 0; i < map.size(); i++)
	{
		if (SDL_IntersectRectAndLine(&map[i], &centerBot.x, &centerBot.y, &centerPlayer.x, &centerPlayer.y))
		{
			noObstaclesBetween = false;
			continue;
		}
	}

	if (noObstaclesBetween && SDL_GetTicks() - fireStart >= fireCallDownMs)
	{
		Fire(bullets);
		fireStart = SDL_GetTicks();
	}
		
}
