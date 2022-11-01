#include "include/raylib.h"
#include "GameManager/gameManager.h"
#include "MenuStates/Gameplay/gameplay.h"

static Player player;
static Obstacle obstacle;

static Texture2D background;
static Texture2D foreground;
static Texture2D buildings;
static Texture2D far_buildings;

static float scrollingBack = 0.0f;
static float scrollingMid = 0.0f;
static float scrollingFore = 0.0f;

float gravity = 500.0f;

int gameplayLoop(bool& initGame, bool backToMenu) 
{
	if (initGame)
	{
		player = initplayer();
		obstacle = initObstacle();
		loadTextures();
		initGame = false;
		backToMenu = false;
	}

	updateGameplay();
	drawGameplay();


	if (backToMenu)
	{
		unloadtextures();
		return static_cast<int>(MenuStates::MainMenu);
	}
	else
	{
		return static_cast<int>(MenuStates::Gameplay);
	}
}

void updateGameplay() 
{
	if (IsKeyDown(KEY_UP))
	{
		gravity = -500.0f;
	}
	else
	{
		gravity += 500.0f * GetFrameTime();
	}


	moveParallax();
	movePlayer(player);
	moveObstacle(obstacle);
	checkOutOfBounds();
	checkColitions();
}

void moveParallax() 
{
	scrollingBack -= 10.0f * GetFrameTime();
	scrollingMid -= 50.0f * GetFrameTime();
	scrollingFore -= 100.0f * GetFrameTime();

	// NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
	if (scrollingBack <= -background.width * 3) scrollingBack = 0;
	if (scrollingMid <= -far_buildings.width * 3) scrollingMid = 0;
	if (scrollingMid <= -buildings.width * 3) scrollingMid = 0;
	if (scrollingFore <= -foreground.width * 3) scrollingFore = 0;
}

void drawGameplay() 
{
	ClearBackground(BLACK);
	BeginDrawing();

	drawParallax();

	DrawText(TextFormat("V 0.1"), 1, 1,40, RED);

	drawPlayer(player);
	drawObstacle(obstacle);

	EndDrawing();
}

void drawParallax() 
{
	ClearBackground(GetColor(0x052c46ff));

	// Draw background image twice
	// NOTE: Texture is scaled twice its size
	DrawTextureEx(background, Vector2 { scrollingBack, 20 }, 0.0f, 5.0f, WHITE);
	DrawTextureEx(background, Vector2 { background.width * 2 + scrollingBack, 20 }, 0.0f, 5.0f, WHITE);

	// Draw midground image twice
	DrawTextureEx(far_buildings, Vector2 { scrollingMid, 20 }, 0.0f, 5.0f, WHITE);
	DrawTextureEx(far_buildings, Vector2 { far_buildings.width * 2 + scrollingMid, 20 }, 0.0f, 5.0f, WHITE);

	// Draw midground image twice
	DrawTextureEx(buildings, Vector2 { scrollingMid, 20 }, 0.0f, 5.0f, WHITE);
	DrawTextureEx(buildings, Vector2 { buildings.width * 2 + scrollingMid, 20 }, 0.0f, 5.0f, WHITE);

	// Draw foreground image twice
	DrawTextureEx(foreground, Vector2 { scrollingFore, 70 }, 0.0f, 5.0f, WHITE);
	DrawTextureEx(foreground, Vector2 { foreground.width * 2 + scrollingFore, 70 }, 0.0f, 5.0f, WHITE);
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

void loadTextures() 
{
	background = LoadTexture("res/skill-desc_0003_bg.png");
	foreground = LoadTexture("res/skill-desc_0000_foreground.png");
	buildings = LoadTexture("res/skill-desc_0001_buildings.png");
	far_buildings = LoadTexture("res/skill-desc_0002_far-buildings.png");
}

void unloadtextures() 
{
	UnloadTexture(background);
	UnloadTexture(foreground);
	UnloadTexture(buildings);
	UnloadTexture(far_buildings);
}