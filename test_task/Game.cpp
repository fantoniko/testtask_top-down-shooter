#include "Game.h"

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	LPCSTR windowName = "top-down shooter";
	mainWindow = SDL_CreateWindow(windowName, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	HWND hWnd = FindWindow(NULL, windowName);
	hDC = GetWindowDC(hWnd);

	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);

	running = true;

	{
		walls.push_back({ 200, 200, 50, 200 });
		walls.push_back({ 300, 500, 200, 50 });
		walls.push_back({ 300, 0, 400, 30 });
		walls.push_back({ 350, 320, 70, 70 });
		walls.push_back({ 700, 100, 50, 450 });
		walls.push_back({ 0, 0, 50, 300 });
	}
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}

void Game::Start()
{

	while(running)
	{
		FPS_Control locker(renderer); // special FPS control class

		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_q:
					mainPlayer.TurnSight(COUNTERCLOCKWISE);
					break;
				case SDLK_e:
					mainPlayer.TurnSight(CLOCKWISE);
					break;
				}
				break;
			}
			/* handle your event here */

			//User requests quit
			if (event.type == SDL_QUIT)
				running = false;
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
		for (auto i = walls.begin(); i < walls.end(); i++)
			SDL_RenderDrawRect(renderer, i._Ptr);

		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
		mainPlayer.Show(renderer);
	}
}

