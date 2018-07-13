#include "FPS_Control.h"

SDL_Renderer* FPS_Control::renderer = NULL;

FPS_Control::FPS_Control(SDL_Renderer* renderer)
{
	//	Получение тика программы в начале игрового цикла
	startTimeOfFrame = SDL_GetTicks();
	//	Установка указателя на используемый Renderer
	if(this->renderer == NULL)
		this->renderer = renderer;
	//	Изменение цвета рисовки Renderer'a
	SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	//	Очистка экрана
	SDL_RenderClear(this->renderer);
}

FPS_Control::~FPS_Control()
{
	//	Отображение содержимого буфера Renderer'a на экран
	SDL_RenderPresent(renderer);
	//	Задержка обработки следующего игрового цикла в соответствии с ограничением FPS
	if (1000 / FPS_LOCK > (SDL_GetTicks() - startTimeOfFrame))
		SDL_Delay(1000 / FPS_LOCK - (SDL_GetTicks() - startTimeOfFrame));
}
