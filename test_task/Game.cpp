#include "Game.h"

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	LPCSTR windowName = "top-down shooter";
	mainWindow = SDL_CreateWindow(windowName, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);

	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	running = true;
	showHitBoxes = false;

	bullets.clear();
	{
		map.push_back({ 200, 200, 50, 200 });
		map.push_back({ 300, 500, 200, 50 });
		map.push_back({ 300, 0, 400, 30 });
		map.push_back({ 350, 320, 70, 70 });
		map.push_back({ 700, 100, 50, 450 });
		map.push_back({ 0, 0, 50, 300 });
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
		FPS_Control locker(renderer);
		EventHandler();
		LogicUpdater();
		ScreenUpdater();
	}
}

void Game::EventHandler()
{
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
			case SDLK_ESCAPE:
				running = false;
				break;
			case SDLK_F1:
				if (showHitBoxes)
					showHitBoxes = false;
				else
					showHitBoxes = true;
				break;
			case SDLK_q:
				mainPlayer.TurnSight(TURN_COUNTERCLOCKWISE);
				break;
			case SDLK_e:
				mainPlayer.TurnSight(TURN_CLOCKWISE);
				break;
			case SDLK_w:
				mainPlayer.Move(map, MOVE_FORWARD);
				break;
			case SDLK_s:
				mainPlayer.Move(map, MOVE_BACKWARD);
				break;
			case SDLK_a:
				mainPlayer.Move(map, MOVE_LEFT);
				break;
			case SDLK_d:
				mainPlayer.Move(map, MOVE_RIGHT);
				break;
			case SDLK_f:
				mainPlayer.Fire(bullets);
				break;
			}
			break;
		}
	}
}

void Game::LogicUpdater()
{
	for (auto i = 0; i < bullets.size(); i++)
	{
		SDL_Rect bulletRect = bullets[i].GetRect();
		bullets[i].Move(map);
		if (!Collision(bullets[i].GetRect()))
			bullets.erase(bullets.begin() + i);
	}	
}

void Game::ScreenUpdater()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
	for (auto i = 0; i < map.size(); i++)
		SDL_RenderDrawRect(renderer, &map[i]);

	mainPlayer.Show(renderer, showHitBoxes);

	for (auto i = 0; i < bullets.size(); i++)
		bullets[i].Show(renderer);
}