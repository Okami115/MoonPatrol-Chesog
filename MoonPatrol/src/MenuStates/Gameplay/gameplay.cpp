#include <iostream>
#include "include/raylib.h"
#include "GameManager/gameManager.h"
#include "MenuStates/Gameplay/gameplay.h"

static Player player;
static Obstacle obstacle;
static Enemy landEnemies[maxLandEnemies];
static Enemy flyingEnemies[maxFlyingEnemies];

static Texture2D background;
static Texture2D foreground;
static Texture2D buildings;
static Texture2D far_buildings;

static float scrollingBack = 0.0f;
static float scrollingMid = 0.0f;
static float scrollingFore = 0.0f;
static float landEnemiesTimer = 3.0f;
static float flyingEnemiesTimer = 10.0f;

static int landEnemiesCounter = 0;
static int flyingEnemiesCounter = 0;


float gravity = 500.0f;

void drawPlayerBullets();

void checkInput(bool& backToMenu);

void playerOutOfBounds();

void enemyOutOfBounds();

void playerEnemyColition(Enemy& CurrentEnemy);

int gameplayLoop(bool& initGame, bool& backToMenu)
{
	HideCursor();
	if (initGame)
	{
		player = initplayer();
		obstacle = initObstacle();
		for (int i = 0; i < maxLandEnemies; i++)
		{
			landEnemies[i] = initEnemy(EnemyType::Land);
		}
		for (int i = 0; i < maxFlyingEnemies; i++)
		{
			flyingEnemies[i] = initEnemy(EnemyType::Flying);
		}
		loadTextures();
		initGame = false;
		backToMenu = false;

		landEnemiesTimer = 3.0f;
		flyingEnemiesTimer = 10.0f;

		landEnemiesCounter = 0;
		flyingEnemiesCounter = 0;
	}

	updateGameplay(backToMenu);
	drawGameplay();
	if (player.lives <= 0)
	{
		backToMenu = true;
	}

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

void updateGameplay(bool& backToMenu)
{

  	if (landEnemiesCounter <= maxLandEnemies)
	{
		landEnemiesTimer -= GetFrameTime();
		//std::cout << "Timer : " << landEnemiesTimer << std::endl;
		if (landEnemiesTimer <= 0)
		{
			landEnemiesCounter++;
			landEnemies[landEnemiesCounter].isAlctive = true;
			landEnemiesTimer = 3.0f;
		}
	}
	if (flyingEnemiesCounter <= maxFlyingEnemies)
	{
		flyingEnemiesTimer -= GetFrameTime();
		std::cout << "Timer : " << flyingEnemiesTimer << std::endl;
		if (flyingEnemiesTimer <= 0)
		{
			flyingEnemiesCounter++;
			flyingEnemies[flyingEnemiesCounter].isAlctive = true;
			flyingEnemiesTimer = 10.0f;
		}
	}

	checkInput(backToMenu);
	moveParallax();
	movePlayer(player);
	moveObstacle(obstacle);
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			moveBullet(player.playerAmmo[i]);
		}
	}
	for (int i = 0; i < maxLandEnemies; i++)
	{
		if (landEnemies[i].isAlctive)
		{
			moveEnemy(landEnemies[i]);
		}
	}
	for (int i = 0; i < maxFlyingEnemies; i++)
	{
		if (flyingEnemies[i].isAlctive)
		{
			moveEnemy(flyingEnemies[i]);
		}
	}
	checkOutOfBounds();
	checkColitions(backToMenu);
}

void checkInput(bool& backToMenu)
{
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
	{
		gravity = -500.0f;
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
	{
		gravity += 10.0f;
	}
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		player.CurrentDirection = static_cast<int>(Directions::Left);
	}
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		player.CurrentDirection = static_cast<int>(Directions::Right);
	}
	if (IsKeyReleased(KEY_ESCAPE))
	{
		backToMenu = true;
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		for (int i = 0; i < playerMaxAmmo; i++)
		{
			if (!player.playerAmmo[i].isActive)
			{
				shoot(player.playerAmmo[i], player);
#if _DEBUG
				std::cout << "Shoot " << std::endl;
#endif // _DEBUG

				break;
			}
		}
	}
	else
	{
		gravity += 500.0f * GetFrameTime();
	}
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

	DrawText(TextFormat("V 0.2"), 1, 1, 40, RED);

	drawPlayer(player);
	drawObstacle(obstacle);
	for (int i = 0; i < maxLandEnemies + 1; i++)
	{
		if (landEnemies[i].isAlctive)
		{
			drawEnemy(landEnemies[i]);
		}
	}
	for (int i = 0; i < maxFlyingEnemies + 1; i++)
	{
		if (flyingEnemies[i].isAlctive)
		{
			drawEnemy(flyingEnemies[i]);
		}
	}
	drawPlayerBullets();

	DrawText(TextFormat("Lives %i",player.lives), 1,GetScreenHeight() - 30,20, YELLOW);

	EndDrawing();
}

void drawParallax()
{
	ClearBackground(GetColor(0x052c46ff));

	// Draw background image twice
	// NOTE: Texture is scaled twice its size
	DrawTextureEx(background, Vector2{ scrollingBack, 20 }, 0.0f, 5.0f, WHITE);
	DrawTextureEx(background, Vector2{ background.width * 2 + scrollingBack, 20 }, 0.0f, 5.0f, WHITE);

	// Draw midground image twice
	DrawTextureEx(far_buildings, Vector2{ scrollingMid, 20 }, 0.0f, 5.0f, WHITE);
	DrawTextureEx(far_buildings, Vector2{ far_buildings.width * 2 + scrollingMid, 20 }, 0.0f, 5.0f, WHITE);

	// Draw midground image twice
	DrawTextureEx(buildings, Vector2{ scrollingMid, 20 }, 0.0f, 5.0f, WHITE);
	DrawTextureEx(buildings, Vector2{ buildings.width * 2 + scrollingMid, 20 }, 0.0f, 5.0f, WHITE);

	// Draw foreground image twice
	DrawTextureEx(foreground, Vector2{ scrollingFore, 70 }, 0.0f, 5.0f, WHITE);
	DrawTextureEx(foreground, Vector2{ foreground.width * 2 + scrollingFore, 70 }, 0.0f, 5.0f, WHITE);
}

void drawPlayerBullets()
{
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			drawBullet(player.playerAmmo[i]);
		}
	}
}

void checkColitions(bool& backToMenu)
{
	playerObstacleColition(obstacle, backToMenu);

	for (int i = 0; i < maxLandEnemies; i++)
	{
		if (landEnemies[i].isAlctive)
		{
			playerEnemyColition(landEnemies[i]);
		}
	}
	for (int i = 0; i < maxFlyingEnemies; i++)
	{
		if (flyingEnemies[i].isAlctive)
		{
			playerEnemyColition(flyingEnemies[i]);
		}
	}
}

void playerObstacleColition(Obstacle& currentObstacle, bool& backToMenu)
{
	if (player.pos.x > currentObstacle.pos.x + currentObstacle.widht || player.pos.x + player.widht < currentObstacle.pos.x || player.pos.y > currentObstacle.pos.y + currentObstacle.height || player.pos.y + player.height < currentObstacle.pos.y)
	{
		player.playerColor = GREEN;
	}
	else
	{
		player.playerColor = YELLOW;

		int textLenght = MeasureText("Perdiste", 40);
		DrawText(TextFormat("Perdiste"), (GetScreenWidth() / 2) - (textLenght / 2), (GetScreenHeight() / 2) - 20, 40, RED);
		backToMenu = true;
	}
}

void playerEnemyColition(Enemy& CurrentEnemy) 
{
	if (player.pos.x > CurrentEnemy.pos.x + CurrentEnemy.widht || player.pos.x + player.widht < CurrentEnemy.pos.x || player.pos.y > CurrentEnemy.pos.y + CurrentEnemy.height || player.pos.y + player.height < CurrentEnemy.pos.y)
	{
		player.playerColor = GREEN;
	}
	else
	{
		player.lives -= 1;
	}
}

void checkOutOfBounds()
{
	obstacleOutOfBounds(obstacle);
	playerOutOfBounds();
	enemyOutOfBounds();
}

void obstacleOutOfBounds(Obstacle& currentObstacle)
{
	if (currentObstacle.pos.x < (0 - currentObstacle.widht))
	{
		currentObstacle.pos.x = GetScreenWidth() + currentObstacle.widht;
	}
}

void playerOutOfBounds()
{
	if (player.pos.x <= 0)
	{
		player.CurrentDirection = static_cast<float>(Directions::Stop);
	}
	if (player.pos.x + (player.widht) >= GetScreenWidth())
	{
		player.CurrentDirection = static_cast<float>(Directions::Stop);
	}
}

void bulletOutOfBounds()
{
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].position.y <= 0 && player.playerAmmo[i].isActive)
		{
			player.playerAmmo[i].isActive = false;
		}
	}
}

void enemyOutOfBounds()
{
	for (int i = 0; i < maxLandEnemies; i++)
	{
		if (landEnemies[i].isAlctive && landEnemies[i].pos.x <= 0)
		{
			landEnemies[i].isAlctive = false;
			landEnemiesCounter--;
		}
	}
	for (int i = 0; i < maxFlyingEnemies; i++)
	{
		if (flyingEnemies[i].isAlctive)
		{
			if (flyingEnemies[i].pos.x >= static_cast<float>(GetScreenWidth()))
			{
				flyingEnemies[i].CurrentDirection.x = static_cast<float>(Directions::Left);
			}
			if (flyingEnemies[i].pos.x <= 0)
			{
				flyingEnemies[i].CurrentDirection.x = static_cast<float>(Directions::Right);
			}
			if (flyingEnemies[i].pos.y >= ceilingHeight * 5)
			{
				flyingEnemies[i].CurrentDirection.y = static_cast<float>(Directions::Up);
			}
			if (flyingEnemies[i].pos.y <= ceilingHeight)
			{
				flyingEnemies[i].CurrentDirection.y = static_cast<float>(Directions::Down);
			}
		}
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