#pragma once
#include <cmath>
#include <string>
#include "Windows.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "KeyboardHandler.h"
#include "FPS_Control.h"
#include "BotPlayer.h"

//	���������, ���������� ������� ������� ����
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

//	����� ������ � ����� ������
class Game
{
	//	�������� ������������ ����
	static const int SCREEN_WIDTH	= 900;
	static const int SCREEN_HEIGHT	= 600;
	
	//	��������� �� ������� ����
	SDL_Window* mainWindow;
	//	��������� �� Renderer ��� �������� ����
	SDL_Renderer* renderer;
	//	������������� ������� �������� ����
	SDL_Rect screenRect;
	//	��������� �� ������������ ����� ��� ����������� �����
	TTF_Font* font;
	//	�������� ��� ����������� �����
	SDL_Texture* scoreTexture;
	//	������������� ������� ����������� �����
	SDL_Rect scoreRect;

	//	���� ������ ���������
	bool running;
	//	���� ����������� �������� ������
	bool roundContinues;
	//	���� ����������� ��������� ��������
	bool showHitBoxes;

	//	��������� ������� ����������
	KeyboardHandler keyHandler;
	//	�������� �����
	Player mainPlayer;
	//	�����, ����������� �����������
	BotPlayer botPlayer;
	//	������� ����
	GameScore score;
	//	������ ���� �� ������
	std::vector<SDL_Rect> map;
	//	������ ����, ����������� � ����
	std::vector<Bullet> bullets;

private:
	//	��������� ������� ����������
	void EventHandler();
	//	��������� ������ ����
	void LogicUpdater();
	//	��������� ����������� �� ������
	void ScreenUpdater();
	//	������� ����� ���������� ������
	void Restart(RoundEnding roundEnding);

public:
	Game();
	~Game();

	//	����� ����
	void Start();
};

