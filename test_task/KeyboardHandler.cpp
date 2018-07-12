#include "KeyboardHandler.h"

void KeyboardHandler::UpdateKeyStates()
{
	SDL_PumpEvents();
	keyArray = (Uint8*)(SDL_GetKeyboardState(NULL));
}

bool KeyboardHandler::IsKeyTapped(SDL_Scancode key)
{
	if (keyArray[key] == 1)
	{
		keyArray[key] = 0;
		return true;
	}
	return false;
}

bool KeyboardHandler::IsKeyDown(SDL_Scancode key)
{
	if (keyArray[key] == 1)
		return true;
	return false;
}

SDL_Event KeyboardHandler::GetEvent()
{
	return event;
}