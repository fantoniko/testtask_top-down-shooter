#include "Bullet.h"

const int Bullet::BULLET_BOX_SIZE					= 5;
const int Bullet::BULLET_MOVE_STEP					= 6;
const double Bullet::BULLET_CIRCLE_LINE_STEP		= 0.5;

Bullet::Bullet(const SDL_Point& start, const Vector2D& direction)
{
	this->direction = direction;
	rect = { start.x, start.y, BULLET_BOX_SIZE, BULLET_BOX_SIZE };
}

void Bullet::Move(const std::vector<SDL_Rect>& map)
{
	//	��������� ��������� � ������������ � ������������ � �����
	rect.x += direction.x * BULLET_MOVE_STEP;
	rect.y += direction.y * BULLET_MOVE_STEP;

	//	�������� �� �������� � ����������� ����������
	for (auto i = 0; i < map.size(); i++)
	{
		if (Collision(map[i]))
			ReflectDirection(map[i]);
	}
}

void Bullet::Show(SDL_Renderer* renderer, bool showHitBoxes)
{
	//	��������� ����� � ��������� ����� ��� ������ ���� 
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	DrawCircle(renderer, rect, BULLET_CIRCLE_LINE_STEP);

	//	���. ����������� ��������� ����
	if (showHitBoxes)
		SDL_RenderDrawRect(renderer, &rect);
}

SDL_Rect Bullet::GetRect()
{
	return rect;
}

void Bullet::ReflectDirection(SDL_Rect wall)
{
	//	����������� ��������� �������� ��� ������ ������ ��������� ��������
	int offsetCoef = 4;
	//	�����-����� �������-����������
	SDL_Point point1, point2;

	//	��������� ����������� �������� �� �������� ����� ��� ������������ �����������
	//	��� ����, � �������� ����� ��������� �����������
	CompassVectorDirection cvd = GetCompassDirection();
	switch (cvd)
	{
	//	�������� � ����������� ������-������� => ������������ ����� ��������� 
	//	� ������ ���� ����� ���������� �����
	//	����������� ������ ��������� ����������� ��������� ������� ������������� �� x � y
	case COMPASS_NORTHEAST:
		if (rect.x + rect.w - wall.x >= wall.y + wall.h - rect.y)
		{
			point1 = { wall.x, wall.y + wall.h };
			point2 = { wall.x + wall.w, wall.y + wall.h };
		}
		else 
		{
			point1 = { wall.x, wall.y};
			point2 = { wall.x, wall.y + wall.h };
		}
		// ��������� �������� �� ����������� �������� �������� 
		// ��� ��������� ����� � ������������ ���� � ������
		rect.x -= BULLET_MOVE_STEP / offsetCoef;
		rect.y += BULLET_MOVE_STEP / offsetCoef;
		break;

	//	�������� � ����������� ������-������ => ������������ ����� ��������� 
	//	� ������ ���� ������ ���������� �����
	//	-//-
	case COMPASS_NORTHWEST:
		if (wall.x + wall.w - rect.x >= wall.y + wall.h - rect.y)
		{
			point1 = { wall.x, wall.y + wall.h };
			point2 = { wall.x + wall.w, wall.y + wall.h };
		}
		else
		{
			point1 = { wall.x + wall.w, wall.y + wall.h };
			point2 = { wall.x + wall.w, wall.y };
		}
		// -//-
		rect.x += BULLET_MOVE_STEP / offsetCoef;
		rect.y += BULLET_MOVE_STEP / offsetCoef;
		break;

		//	�������� � ����������� ���-������ => ������������ ����� ��������� 
		//	� ������� ���� ������ ���������� �����
		//	-//-
	case COMPASS_SOUTHWEST:
		if (wall.x + wall.w - rect.x >= rect.y + rect.h - wall.y)
		{
			point1 = { wall.x + wall.w, wall.y };
			point2 = { wall.x, wall.y };
		}
		else
		{
			point1 = { wall.x + wall.w, wall.y + wall.h };
			point2 = { wall.x + wall.w, wall.y };
		}
		// -//-
		rect.x += BULLET_MOVE_STEP / offsetCoef;
		rect.y -= BULLET_MOVE_STEP / offsetCoef;
		break;

		//	�������� � ����������� ���-������� => ������������ ����� ��������� 
		//	� ������� ���� ����� ���������� �����
		//	-//-
	case COMPASS_SOUTHEAST:
		if (rect.x + rect.w - wall.x >= rect.y + rect.h - wall.y)
		{
			point1 = { wall.x + wall.w, wall.y };
			point2 = { wall.x, wall.y };
		}
		else
		{
			point1 = { wall.x, wall.y };
			point2 = { wall.x, wall.y + wall.h };
		}
		//	-//-
		rect.x -= BULLET_MOVE_STEP / offsetCoef;
		rect.y -= BULLET_MOVE_STEP / offsetCoef;
		break;

	default:
		break;
	}
	//	��������� ������� �� ��������� ����� ���������-����������
	Vector2D reflectiveSurface(point1, point2);
	//	��������� �������-������� � ���������-����������
	Vector2D surfaceNormal(reflectiveSurface.y, -reflectiveSurface.x);
	//	������������ �������
	surfaceNormal.Normalize();
	//	��������� ����������� �������
	direction = direction - surfaceNormal * 2 * (direction * surfaceNormal);
}

CompassVectorDirection Bullet::GetCompassDirection()
{
	//��������� ����������� ������� � �������� ����� �� ���������� x � y
	if (direction.y >= 0)
	{
		if (direction.x >= 0)
			return COMPASS_SOUTHEAST;
		else
			return COMPASS_SOUTHWEST;
	}
	else
	{
		if (direction.x >= 0)
			return COMPASS_NORTHEAST;
		else
			return COMPASS_NORTHWEST;
	}
}
