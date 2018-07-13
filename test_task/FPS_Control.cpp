#include "FPS_Control.h"

SDL_Renderer* FPS_Control::renderer = NULL;

FPS_Control::FPS_Control(SDL_Renderer* renderer)
{
	//	��������� ���� ��������� � ������ �������� �����
	startTimeOfFrame = SDL_GetTicks();
	//	��������� ��������� �� ������������ Renderer
	if(this->renderer == NULL)
		this->renderer = renderer;
	//	��������� ����� ������� Renderer'a
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	//	������� ������
	SDL_RenderClear(this->renderer);
}

FPS_Control::~FPS_Control()
{
	//	����������� ����������� ������ Renderer'a �� �����
	SDL_RenderPresent(renderer);
	//	�������� ��������� ���������� �������� ����� � ������������ � ������������ FPS
	if (1000 / FPS_LOCK > (SDL_GetTicks() - startTimeOfFrame))
		SDL_Delay(1000 / FPS_LOCK - (SDL_GetTicks() - startTimeOfFrame));
}
