#pragma once
#include "Player.h"
#include <ctime>

//	Класс управляемого компьютером игрока
class BotPlayer : public Player
{	
	//	Счетчик для обновления данных и логики бота
	int botUpdateChecker;
	//	Флаг отсутствия препятствий между игроками
	bool noObstaclesBetween;

public:
	BotPlayer();
	
	//	Проверка на дозволенность обновления бота
	bool UpdateChecker(int limit);
	//	Обновление позиции и логики бота
	void Update(const std::vector<SDL_Rect>& map, std::vector<Bullet>& bullets, const SDL_Rect playerRect);
};
