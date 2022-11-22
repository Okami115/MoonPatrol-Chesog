#include "include/raylib.h"
#include "GameManager/gameManager.h"
#include "MenuStates/Gameplay/GamePlay.h"
#include "MenuStates/MainMenu/mainMenu.h"

void executeGame() 
{
	int screenWidth = 1024;
	int screenHeight = 768;

	int menuAnsw = (int)MenuStates::MainMenu;
	int point = 0;

	bool backToMenu = false;
	bool reset = true;

	extern bool isMultiplayer;

	InitWindow(screenWidth, screenHeight, "Asteroids");

	HideCursor();
	SetExitKey(KEY_NULL);


	bool initGame = true;


	while (!WindowShouldClose())
	{
		switch (menuAnsw)
		{
		case (int)MenuStates::MainMenu:
			backToMenu = false;
			reset = true;
			isMultiplayer = false;
			initGame = true;
			menuAnsw = mainMenu(point);
			break;
		case (int)MenuStates::MultiPlayer:
			isMultiplayer = true;
		case (int)MenuStates::SinglePlayer:
			menuAnsw = gameplayLoop(initGame, backToMenu);
			break;
		case (int)MenuStates::Rules:
			menuAnsw = (int)MenuStates::MainMenu;
			break;
		case (int)MenuStates::Credits:
			menuAnsw = (int)MenuStates::MainMenu;
			break;
		case (int)MenuStates::Options:
			menuAnsw = (int)MenuStates::MainMenu;
			break;
		case (int)MenuStates::Exit:
			return;
			break;
		}
	}

	CloseWindow();
}
