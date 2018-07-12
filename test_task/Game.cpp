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

	map.push_back({ 200, 200, 50, 200 });
	map.push_back({ 300, 500, 200, 50 });
	map.push_back({ 300, 0, 400, 30 });
	map.push_back({ 350, 320, 70, 70 });
	map.push_back({ 700, 100, 50, 450 });
	map.push_back({ 0, 0, 50, 300 });
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
	keyHandler.UpdateKeyStates();
	
	if (keyHandler.IsKeyTapped(SDL_SCANCODE_F1))
	{
		if (showHitBoxes)
			showHitBoxes = false;
		else
			showHitBoxes = true;
	}

	if (keyHandler.GetEvent().type == SDL_QUIT || keyHandler.IsKeyDown(SDL_SCANCODE_ESCAPE))
		running = false;

	if (keyHandler.IsKeyDown(SDL_SCANCODE_Q))
		mainPlayer.TurnSight(TURN_COUNTERCLOCKWISE);

	if (keyHandler.IsKeyDown(SDL_SCANCODE_E))
		mainPlayer.TurnSight(TURN_CLOCKWISE);

	if (keyHandler.IsKeyDown(SDL_SCANCODE_W))
		mainPlayer.Move(map, MOVE_FORWARD);

	if (keyHandler.IsKeyDown(SDL_SCANCODE_S))
		mainPlayer.Move(map, MOVE_BACKWARD);

	if (keyHandler.IsKeyDown(SDL_SCANCODE_A))
		mainPlayer.Move(map, MOVE_LEFT);

	if (keyHandler.IsKeyDown(SDL_SCANCODE_D))
		mainPlayer.Move(map, MOVE_RIGHT);

	if (keyHandler.IsKeyTapped(SDL_SCANCODE_F))
		mainPlayer.Fire(bullets);

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