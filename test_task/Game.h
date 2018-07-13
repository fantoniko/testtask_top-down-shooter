#pragma once
#include <cmath>
#include <string>
#include "Windows.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "KeyboardHandler.h"
#include "FPS_Control.h"
#include "BotPlayer.h"

//	Структура, содержащая текущий игровой счет
struct GameScore
{
	int playerPoints;
	int botPoints;
};

enum RoundEnding
{
	ROUND_PLAYER_WINS,
	ROUND_BOT_WINS,
	ROUND_TIE
};

//	Класс шутера с видом сверху
class Game
{
	//	Свойства создаваемого окна
	static const int SCREEN_WIDTH	= 900;
	static const int SCREEN_HEIGHT	= 600;
	
	//	Указатель на главное окно
	SDL_Window* mainWindow;
	//	Указатель на Renderer для главного окна
	SDL_Renderer* renderer;
	//	Прямоугольная область главного окна
	SDL_Rect screenRect;
	//	Указатель на используемый шрифт для отображения счета
	TTF_Font* font;
	//	Текстура для отображения счета
	SDL_Texture* scoreTexture;
	//	Прямоугольная область отображения счета
	SDL_Rect scoreRect;

	//	Флаг работы программы
	bool running;
	//	Флаг продолжения текущего раунда
	bool roundContinues;
	//	Флаг отображения хитбоксов объектов
	bool showHitBoxes;

	//	Обаботчик событий клавиатуры
	KeyboardHandler keyHandler;
	//	Основной игрок
	Player mainPlayer;
	//	Игрок, управляемый компьютером
	BotPlayer botPlayer;
	//	Игровой счет
	GameScore score;
	//	Вектор стен на экране
	std::vector<SDL_Rect> map;
	//	Вектор пуль, находящихся в игре
	std::vector<Bullet> bullets;

private:
	//	Обработка событий клавиатуры
	void EventHandler();
	//	Обработка логики игры
	void LogicUpdater();
	//	Обработка отображения на экране
	void ScreenUpdater();
	//	Рестарт после завершения раунда
	void Restart(RoundEnding roundEnding);

public:
	Game();
	~Game();

	//	Старт игры
	void Start();
};

