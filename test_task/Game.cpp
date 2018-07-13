#include "Game.h"

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	font = TTF_OpenFont("Roboto-Black.ttf", 40);
	const char* windowName = "top-down shooter";
	mainWindow = SDL_CreateWindow(windowName, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);

	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	score = { 0, 0 };

	map.push_back({ 200, 200, 50, 200 });
	map.push_back({ 300, 500, 200, 50 });
	map.push_back({ 300, 0, 400, 30 });
	map.push_back({ 350, 320, 70, 70 });
	map.push_back({ 700, 100, 50, 450 });
	map.push_back({ 0, 50, 50, 300 });

	running = true;
	showHitBoxes = false;
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainWindow);
	TTF_Quit();
	SDL_Quit();
}

void Game::Start()
{
	while (running)
	{
		roundContinues = true;
		bullets.clear();
		std::string textGameScore = std::to_string(score.playerPoints) + " : " + std::to_string(score.botPoints);
		int w, h;
		TTF_SizeText(font, textGameScore.c_str(), &w, &h);
		scoreRect = { 0, 0, w ,h };
		SDL_Surface* textSurf = TTF_RenderText_Solid(font, textGameScore.c_str(), SDL_Color{ 255, 255, 255, 0 });
		scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurf);

		mainPlayer.SetPosition(SDL_Point{ 100, 100 });
		botPlayer.SetPosition(SDL_Point{ 600, 500 });

		while (running && roundContinues)
		{
			FPS_Control locker(renderer);
			EventHandler();
			LogicUpdater();
			ScreenUpdater();
		}
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
		bullets[i].Move(map);
		if (!Collision(bullets[i].GetRect()))
		{
			bullets.erase(bullets.begin() + i);
			i--;
			continue;
		}

		if (SDL_HasIntersection(&bullets[i].GetRect(), &mainPlayer.GetRect()))
			Restart(false);
			
		if (SDL_HasIntersection(&bullets[i].GetRect(), &botPlayer.GetRect()))
			Restart(true);
			
	}	

	if(botPlayer.UpdateChecker(1))
		botPlayer.Update(map, bullets, mainPlayer.GetRect());
}

void Game::ScreenUpdater()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
	for (auto i = 0; i < map.size(); i++)
		SDL_RenderDrawRect(renderer, &map[i]);

	mainPlayer.Show(renderer, showHitBoxes);
	botPlayer.Show(renderer, showHitBoxes);

	for (auto i = 0; i < bullets.size(); i++)
		bullets[i].Show(renderer);

	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}

void Game::Restart(bool playerWins)
{
	if (playerWins)
		score.playerPoints++;
	else
		score.botPoints++;

	roundContinues = false;
}
