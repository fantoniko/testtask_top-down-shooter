#include "Game.h"

Game::Game()
{
	//	Инициализация SDL и TTF
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	font = TTF_OpenFont(GetResourcePath("Roboto-Black.ttf").c_str(), 40);
	const char* windowName = "top-down shooter";
	mainWindow = SDL_CreateWindow(windowName, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);

	screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	score = { 0, 0 };

	//	Создание карты из различных стен прямоугольной формы
	map.push_back({ 200, 200, 50, 200 });
	map.push_back({ 300, 500, 200, 50 });
	map.push_back({ 300, 0, 400, 30 });
	map.push_back({ 350, 320, 70, 70 });
	map.push_back({ 700, 100, 50, 250 });
	map.push_back({ 0, 50, 50, 300 });
	
	//	Инициализация флагов
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

		//	Создание текстуры из данных о текущем счете для отображения на экране 
		std::string textGameScore = std::to_string(score.playerPoints) + " : " + std::to_string(score.botPoints);
		int w, h;
		TTF_SizeText(font, textGameScore.c_str(), &w, &h);
		scoreRect = { 0, 0, w ,h };
		SDL_Surface* textSurf = TTF_RenderText_Solid(font, textGameScore.c_str(), SDL_Color{ 255, 255, 255, 0 });
		scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurf);

		//	Постановка игроков на исходные позиции
		mainPlayer.SetPosition(SDL_Point{ 100, 100 });
		botPlayer.SetPosition(SDL_Point{ 600, 500 });

		//	Основной игровой цикл
		while (running && roundContinues)
		{
			//	Контроль FPS, очистка экрана и отображение готовых сцен посредством 
			//	вызовов конструктора и деструктора класса FPS_Control
			FPS_Control locker(renderer);
			EventHandler();
			LogicUpdater();
			ScreenUpdater();
		}
	}
}

void Game::EventHandler()
{
	//	Обновление соостояний клавиш
	keyHandler.UpdateKeyStates();
	
	// Обработка нажатий клавиш управления
	if (keyHandler.IsKeyTapped(SDL_SCANCODE_F1))
	{
		if (showHitBoxes)
			showHitBoxes = false;
		else
			showHitBoxes = true;
	}

	if (keyHandler.IsKeyTapped(SDL_SCANCODE_F2))
		Restart(ROUND_TIE);

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
	//	Проверки на нахождение пули в пределах экрана и коллизию с игроками
	for (auto i = 0; i < bullets.size(); i++)
	{
		bullets[i].Move(map);
		if(!SDL_HasIntersection(&screenRect, &bullets[i].GetRect()))
		{
			bullets.erase(bullets.begin() + i);
			i--;
			continue;
		}

		//	При коллизии с игроком запускается рестарт игры с обновленным счетом
		if (SDL_HasIntersection(&bullets[i].GetRect(), &mainPlayer.GetRect()))
			Restart(ROUND_BOT_WINS);
			
		if (SDL_HasIntersection(&bullets[i].GetRect(), &botPlayer.GetRect()))
			Restart(ROUND_PLAYER_WINS);
			
	}	

	//	Обновление логики бота
	if(botPlayer.UpdateChecker(1))
		botPlayer.Update(map, bullets, mainPlayer.GetRect());
}

void Game::ScreenUpdater()
{
	//	Отображение всех взаимодействующих объектов и текущего счета
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
	for (auto i = 0; i < map.size(); i++)
		SDL_RenderDrawRect(renderer, &map[i]);

	mainPlayer.Show(renderer, showHitBoxes);
	botPlayer.Show(renderer, showHitBoxes);

	for (auto i = 0; i < bullets.size(); i++)
		bullets[i].Show(renderer, showHitBoxes);

	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
}

void Game::Restart(RoundEnding roundEnding)
{
	//	Обновление счета с учетом победы одного из игроков или перезапуска
	switch (roundEnding)
	{
	case ROUND_PLAYER_WINS:
		score.playerPoints++;
		break;
	case ROUND_BOT_WINS:
		score.botPoints++;
		break;
	case ROUND_TIE:
		break;
	}

	roundContinues = false;
}

std::string Game::GetResourcePath(const std::string & subDir)
{
	const char PATH_SEP = '\\';
	static std::string baseRes;
	if (baseRes.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}

		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "Resources" + PATH_SEP;
	}
	return subDir.empty() ? (baseRes).c_str() : std::string(baseRes + subDir).c_str();
}