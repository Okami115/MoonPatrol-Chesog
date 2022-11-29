#include "include/raylib.h"
#include "GameManager/gameManager.h"
#include "MenuStates/Gameplay/GamePlay.h"
#include "MenuStates/MainMenu/mainMenu.h"

void executeGame() 
{
	int screenWidth = 1024;
	int screenHeight = 768;

	int menuAnsw = static_cast<int>(MenuStates::MainMenu);
	int point = 0;

	bool backToMenu = false;
	bool reset = true;

	extern bool isMultiplayer;

	InitWindow(screenWidth, screenHeight, "Moon Patrol Chesog - OkamiDesu - V1.0");
	InitAudioDevice();
	initTexturesAndMusic();
	HideCursor();
	SetExitKey(KEY_NULL);


	bool initGame = true;


	while (!WindowShouldClose())
	{
		playMusic(menuAnsw);
		switch (menuAnsw)
		{
		case static_cast<int>(MenuStates::MainMenu):
			backToMenu = false;
			reset = true;
			isMultiplayer = false;
			initGame = true;
			menuAnsw = mainMenu(point);
			break;
		case static_cast<int>(MenuStates::MultiPlayer):
			isMultiplayer = true;
		case static_cast<int>(MenuStates::Game):
			menuAnsw = gameplayLoop(initGame, backToMenu);
			break;
		case static_cast<int>(MenuStates::Rules):
			menuAnsw = Rules(point);
			break;
		case static_cast<int>(MenuStates::Credits):
			menuAnsw = Credits(point);
			break;
		case static_cast<int>(MenuStates::Options):
			menuAnsw = Options(point);
			break;
		case static_cast<int>(MenuStates::Exit):
			return;
			break;
		}
	}

	UninitTexturesAndMusic();
	CloseWindow();
}
