#pragma once
#include "SDL.h"

//	����� �������� FPS, ����������� ������� ����� � ������� ������
class FPS_Control
{
	//	����������� �� ����. ���-�� FPS
	static const int FPS_LOCK = 60;
	//	��������� �� Renderer ��� ������������ ����
	static SDL_Renderer* renderer;
	//	��� ��������� � ������ �������� �����
	Uint32 startTimeOfFrame;

public:
	FPS_Control(SDL_Renderer* renderer);
	~FPS_Control();
};

