#include "include/raylib.h"
#include "GameManager/gameManager.h"
#include "MenuStates/Gameplay/gameplay.h"

void executeGame() 
{
	int screenWidth = 1024;
	int screenHeight = 768;

	int menuAnsw = (int)MenuStates::Gameplay;
	bool backToMenu = false;
	bool reset = true;



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
			initGame = true;
			break;
		case (int)MenuStates::Gameplay:
			menuAnsw = gameplayLoop(initGame, backToMenu);
			break;
		case (int)MenuStates::Rules:
			break;
		case (int)MenuStates::Credits:
			break;
		case (int)MenuStates::Options:
			break;
		case (int)MenuStates::Exit:
			return;
			break;
		}
	}

	CloseWindow();
}
