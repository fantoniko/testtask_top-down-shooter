#pragma once
#include "SDL.h"
#include "ActiveObject.h"

//	������������ ������������ ����������� �� ��������� ������ �����
enum CompassVectorDirection
{
	COMPASS_NORTHEAST,
	COMPASS_NORTHWEST,
	COMPASS_SOUTHWEST,
	COMPASS_SOUTHEAST
};

//	����� ����
class Bullet : ActiveObject 
{
	//	������ �������� ����
	static const int BULLET_BOX_SIZE;
	//	��� �������� ����
	static const int BULLET_MOVE_STEP;
	//	��� ����������� ������ ����
	static const double BULLET_CIRCLE_LINE_STEP;

private:
	//	��������� ���������� �� �����
	void ReflectDirection(SDL_Rect wall);
	//	��������� ����������� ������� �� ������� ������ �����
	CompassVectorDirection GetCompassDirection();

public:
	//	����������� � ��������� ������ ��������� � ������������ ��������
	Bullet(const SDL_Point& start, const Vector2D& direction);

	//	�������� � ��������� �� �������� �� �������
	void Move(const std::vector<SDL_Rect>& map);
	//	����������� �� �����
	void Show(SDL_Renderer* renderer, bool showHitBoxes);
	//	��������� ��������� ��������
	SDL_Rect GetRect();
};

