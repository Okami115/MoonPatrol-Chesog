#include "include/raylib.h"
#include "GameManager/gameManager.h"
#include "MenuStates/Gameplay/gameplay.h"

static Player player;
static Obstacle obstacle;

int gameplayLoop(bool& initGame, bool backToMenu) 
{
	if (initGame)
	{
		player = initplayer();
		obstacle = initObstacle();
		initGame = false;
		backToMenu = false;
	}

	updateGameplay();
	drawGameplay();

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
	moveObstacle(obstacle);
	checkOutOfBounds();
	checkColitions();
}

void drawGameplay() 
{
	ClearBackground(BLACK);
	BeginDrawing();

	DrawText(TextFormat("V 0.1"), 1, 1,40, RED);

	drawPlayer(player);
	drawObstacle(obstacle);

	EndDrawing();
}

void checkColitions() 
{
	playerObstacleColition(obstacle);
}

void playerObstacleColition(Obstacle& currentObstacle)
{
	if (player.pos.x > currentObstacle.pos.x + currentObstacle.widht || player.pos.x + player.widht < currentObstacle.pos.x || player.pos.y > currentObstacle.pos.y + currentObstacle.height || player.pos.y + player.height < currentObstacle.pos.y)
	{
		player.playerColor = GREEN;
	}
	else
	{
		player.playerColor = YELLOW;

		int textLenght = MeasureText("Perdiste",40);
		DrawText(TextFormat("Perdiste"),(GetScreenWidth() / 2) - (textLenght / 2),(GetScreenHeight() / 2) - 20 , 40, RED);
	}
}

void checkOutOfBounds() 
{
	obstacleOutOfBounds(obstacle);
}

void obstacleOutOfBounds(Obstacle& currentObstacle) 
{
	if (currentObstacle.pos.x < ( 0 - currentObstacle.widht))
	{
		currentObstacle.pos.x = GetScreenWidth() + currentObstacle.widht;
	}
}