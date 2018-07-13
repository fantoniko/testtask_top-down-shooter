#include "Player.h"

const int Player::PLAYER_BOX_SIZE					= 40;
const double Player::DELTA_TURN						= 0.1;
const int Player::PLAYER_MOVE_STEP					= 5;
const double Player::PLAYER_CIRCLE_LINE_STEP		= 0.05;
const int Player::FIRE_CALLDOWN_MS					= 100;

Player::Player()
{
	direction = Vector2D(0, 1);
	rect = { 500, 300, PLAYER_BOX_SIZE, PLAYER_BOX_SIZE };
}

void Player::TurnSight(TurnPlayer turnPlayer)
{
	//ѕоворот вектора направлени€ через матрицу поворота, расписанную в изменени€х координат
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
	//»зменение вектора скорости в зависимости от переданного в метод направлени€ движени€
	speedVector = Vector2D(0, 0);
	SDL_Rect tempRect = rect;
	switch (moveDirection)
	{
	case MOVE_FORWARD:
		speedVector = speedVector + direction * PLAYER_MOVE_STEP;
		break;
	case MOVE_BACKWARD:
		speedVector = speedVector - direction * PLAYER_MOVE_STEP;
		break;
	case MOVE_LEFT:
		speedVector.x = speedVector.x + direction.y * PLAYER_MOVE_STEP;
		speedVector.y = speedVector.y - direction.x * PLAYER_MOVE_STEP;
		break;
	case MOVE_RIGHT:
		speedVector.x = speedVector.x - direction.y * PLAYER_MOVE_STEP;
		speedVector.y = speedVector.y + direction.x * PLAYER_MOVE_STEP;
		break;
	}
	rect.x += speedVector.x;
	rect.y += speedVector.y;

	//ѕроверка на коллизии со стенами и возврат к исходной позиции при их наличии
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
	//ѕроверка на наличие штрафа по времени на выстрел и последующее создание новой пули
	if (SDL_GetTicks() - fireStart >= FIRE_CALLDOWN_MS)
	{
		bullets.push_back(Bullet(playerCursor, direction));
		fireStart = SDL_GetTicks();
	}
}

void Player::SetPosition(const SDL_Point& coords)
{
	rect = { coords.x, coords.y, PLAYER_BOX_SIZE, PLAYER_BOX_SIZE };
	direction.x = 0;
	direction.y = 1;
}

void Player::Show(SDL_Renderer* renderer, bool showHitBoxes)
{
	//ќтрисовка изображени€ круга и курсора игрока
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
	DrawCircle(renderer, rect, PLAYER_CIRCLE_LINE_STEP);
	int centerX = rect.x + rect.w / 2;
	int centerY = rect.y + rect.h / 2;
	playerCursor.x = centerX + direction.x * PLAYER_BOX_SIZE / 1.2;
	playerCursor.y = centerY + direction.y * PLAYER_BOX_SIZE / 1.2;

	SDL_RenderDrawLine(renderer, centerX, centerY, playerCursor.x, playerCursor.y);

	//ƒоп. отображение хитбоксов игроков
	if(showHitBoxes)
		SDL_RenderDrawRect(renderer, &rect);
}