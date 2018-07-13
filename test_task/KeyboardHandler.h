#pragma once
#include <SDL.h>

//	����� ����������� ������� ����������
class KeyboardHandler
{
private:
	//	������ ���� ������
	Uint8* keyArray;
	//	SDL_�������
	SDL_Event event;

public:
	//	���������� ��������� ������
	void UpdateKeyStates();
	//	�������� �� �������
	bool IsKeyTapped(SDL_Scancode key);
	//	�������� �� ��������� �������
	bool IsKeyDown(SDL_Scancode key);
	//	��������� SDL-�������
	SDL_Event GetEvent();
};