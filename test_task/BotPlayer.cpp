#include "BotPlayer.h"

BotPlayer::BotPlayer()
{
	direction.x = 0;
	direction.y = -1;
	rect = { 500, 300, PLAYER_BOX_SIZE, PLAYER_BOX_SIZE };
}

bool BotPlayer::UpdateChecker(int limit)
{
	// Возвращает true, если обновление разрешено
	// Возвращает false, если прошло недостаточно игровых циклов с прошлого обновления
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
	//	Координаты центров обоих игроков
	SDL_Point centerBot = { rect.x + rect.w / 2, rect.y + rect.h / 2 };
	SDL_Point centerPlayer = { playerRect.x + playerRect.w / 2, playerRect.y + playerRect.h / 2 };
	//	Изменение направления в сторону игрока
	direction = Vector2D(centerBot, centerPlayer).Normalize();

	//	Генерация случайного направления движения из четырех базовых
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

	//	Проверка на наличие объектов между игроками 
	noObstaclesBetween = true;
	for (auto i = 0; i < map.size(); i++)
	{
		if (SDL_IntersectRectAndLine(&map[i], &centerBot.x, &centerBot.y, &centerPlayer.x, &centerPlayer.y))
		{
			noObstaclesBetween = false;
			continue;
		}
	}

	//	Выстрел, если не найдено объектов пересекающих траекторию
	if (noObstaclesBetween)
		Fire(bullets);
		
}
