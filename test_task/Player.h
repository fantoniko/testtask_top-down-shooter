#pragma once
#include "ActiveObject.h"
#include "Bullet.h"

//Перечисление набора поворотов взгляда
enum TurnPlayer
{
	TURN_CLOCKWISE,
	TURN_COUNTERCLOCKWISE
};

//Перечисление набора направлений движения
enum MoveDirection
{
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
};

//Класс игроков
class Player : public ActiveObject
{
protected:
	//Размер хитбокса игрока
	static const int PLAYER_BOX_SIZE;
	//Дельта угол поворота взгляда (в радианах)
	static const double DELTA_TURN;
	//Шаг игрока при движении
	static const int PLAYER_MOVE_STEP;
	//Шаг детализации модели круга 
	static const double PLAYER_CIRCLE_LINE_STEP;
	//Штраф на использование выстрела (в милисекундах)
	static const int FIRE_CALLDOWN_MS;

	//Вектор скорости
	Vector2D speedVector;
	//Координаты внешнего края курсора игрока
	SDL_Point playerCursor;
	//Тик программы во время выстрела
	Uint32 fireStart;

public:
	Player();

	//Поворот взгляда
	void TurnSight(TurnPlayer turnPlayer);
	//Отображение игрока на экране с доп. флагом отображения хитбокса
	void Show(SDL_Renderer* renderer, bool showPlayerHitBoxes);
	//Движение в заданном направлении с проверкой коллизий со стенами
	void Move(const std::vector<SDL_Rect>& map, MoveDirection moveDirection);
	//Выстрел
	void Fire(std::vector<Bullet>& bullets);
	//Установка позиции на экране
	void SetPosition(const SDL_Point& coords);
};
