#include "MenuStates/Gameplay/gameplay.h"
#include "Objets/Player/player.h"
#include "GameManajer/gameManajer.h"

static Player player;

int gameplayLoop(bool initGame, bool backToMenu) 
{
	if (initGame)
	{
		player = initplayer();
		initGame = false;
		backToMenu = false;
	}

	drawGameplay();
	updateGameplay();

	return static_cast<int>(MenuStates::Gameplay);
}
void updateGameplay() 
{
	if (IsKeyPressed(KEY_UP))
	{
		player.CurrentDirection = static_cast<float>(Directions::Up);
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		player.CurrentDirection = static_cast<float>(Directions::Down);
	}
	movePlayer(player);
}
void drawGameplay() 
{
	drawPlayer(player);
}