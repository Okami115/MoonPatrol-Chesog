#include <iostream>
#include "include/raylib.h"
#include "GameManager/gameManager.h"
#include "GamePlay.h"

static Player player;
static Player player2;
static Enemy landEnemies[maxLandEnemies];
static Enemy flyingEnemies[maxFlyingEnemies];

bool isMultiplayer = false;

static Texture2D background;
static Texture2D foreground;
static Texture2D buildings;
static Texture2D far_buildings;

static float scrollingBack = 0.0f;
static float scrollingMid = 0.0f;
static float scrollingFore = 0.0f;
static float landEnemiesTimer = 3.0f;
static float flyingEnemiesTimer = 5.0f;
static float playerTimer = 2.0f;

static int landEnemiesCounter = 0;
static int flyingEnemiesCounter = 0;


float gravity = 500.0f;
float gravity2 = 500.0f;

void drawPlayerBullets();

void checkInput(bool& backToMenu);

void playerOutOfBounds();

void enemyOutOfBounds();

void playerEnemyColition(Enemy& CurrentEnemy);

void bulletEnemyColition(Enemy& CurrentEnemy, Bullet& currentBullet);

int gameplayLoop(bool& initGame, bool& backToMenu)
{
	HideCursor();
	if (initGame)
	{
		player = initplayer(false);
		if (isMultiplayer)
		{
			player2 = initplayer(true);
		}

		for (int i = 0; i < maxLandEnemies; i++)
		{
			if (i < maxLandEnemies / 2 && isMultiplayer)
			{
				landEnemies[i] = initEnemy(EnemyType::Land, true);
			}
			else
			{
				landEnemies[i] = initEnemy(EnemyType::Land, false);
			}
		}
		for (int i = 0; i < maxFlyingEnemies; i++)
		{
			flyingEnemies[i] = initEnemy(EnemyType::Flying, false);
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
	if (player.lives <= 0 || player2.lives <= 0 && isMultiplayer)
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
		return static_cast<int>(MenuStates::SinglePlayer);
	}
}

void updateGameplay(bool& backToMenu)
{

	if (landEnemiesCounter < maxLandEnemies)
	{
		landEnemiesTimer -= GetFrameTime();
		if (landEnemiesTimer < 0)
		{
			landEnemies[landEnemiesCounter].isActive = true;
			landEnemiesTimer = 2.0f;
			landEnemiesCounter++;
		}
	}

	if (flyingEnemiesCounter < maxFlyingEnemies)
	{
		flyingEnemiesTimer -= GetFrameTime();
		if (flyingEnemiesTimer < 0)
		{
			flyingEnemies[flyingEnemiesCounter].isActive = true;
			flyingEnemiesTimer = 5.0f;
			flyingEnemiesCounter++;
		}
	}


	checkInput(backToMenu);
	moveParallax();
	movePlayer(player, false);
	if (isMultiplayer)
	{
		movePlayer(player2, true);
	}

	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			moveBullet(player.playerAmmo[i]);
		}

		if (isMultiplayer)
		{
			if (player2.playerAmmo[i].isActive)
			{
				moveBullet(player2.playerAmmo[i]);
			}
		}
	}
	for (int i = 0; i < maxLandEnemies; i++)
	{
		if (landEnemies[i].isActive)
		{
			moveEnemy(landEnemies[i]);
		}
	}
	for (int i = 0; i < maxFlyingEnemies; i++)
	{
		if (flyingEnemies[i].isActive)
		{
			moveEnemy(flyingEnemies[i]);
		}
	}
	if (player.isHit)
	{
		if (playerTimer <= 0)
		{
			player.isHit = false;
		}
		else
		{
			playerTimer -= GetFrameTime();
		}
	}

	if (player2.isHit && isMultiplayer)
	{
		if (playerTimer <= 0)
		{
			player2.isHit = false;
		}
		else
		{
			playerTimer -= GetFrameTime();
		}
	}
	checkOutOfBounds();
	checkColitions();
}

void checkInput(bool& backToMenu)
{
	if (IsKeyReleased(KEY_ESCAPE))
	{
		backToMenu = true;
	}
	if (IsKeyDown(KEY_W))
	{
		if (player.pos.y == static_cast<float>(GetScreenHeight()) - floorHeight)
		{
			gravity = -500.0f;
		}
	}
	if (IsKeyDown(KEY_S))
	{
		gravity += 5.0f * GetFrameTime();
	}
	if (IsKeyDown(KEY_A))
	{
		player.CurrentDirection = static_cast<int>(Directions::Left);
	}
	if (IsKeyDown(KEY_D))
	{
		player.CurrentDirection = static_cast<int>(Directions::Right);
	}
	if (IsKeyPressed(KEY_SPACE))
		{
			for (int i = 0; i < playerMaxAmmo; i++)
			{
				if (!player.playerAmmo[i].isActive)
				{
					shoot(player.playerAmmo[i], player);
					break;
				}
				else if (player.playerAmmo[i].position.y < 0)
				{
					player.playerAmmo[i].isActive = false;
				}
			}
		}
	else
	{
		gravity += 500.0f * GetFrameTime();
	}
	if (isMultiplayer)
	{
		if (IsKeyDown(KEY_UP))
		{
			if (player2.pos.y == static_cast<float>(GetScreenHeight()) - floorHeight2)
			{
				gravity2 = -500.0f;
			}
		}
		if (IsKeyDown(KEY_DOWN))
		{
			gravity2 += 5.0f * GetFrameTime();
		}
		if (IsKeyDown(KEY_LEFT))
		{
			player2.CurrentDirection = static_cast<int>(Directions::Left);
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			player2.CurrentDirection = static_cast<int>(Directions::Right);
		}
		if (IsKeyPressed(KEY_P))
	{
			for (int i = 0; i < playerMaxAmmo; i++)
			{
				if (!player2.playerAmmo[i].isActive)
				{
					shoot(player2.playerAmmo[i], player2);
					break;
				}
				else if (player2.playerAmmo[i].position.y < 0)
				{
					player2.playerAmmo[i].isActive = false;
				}
			}
	}
		else
		{
			gravity2 += 500.0f * GetFrameTime();
		}
	}
}

void moveParallax()
{
	scrollingBack -= 1000.0f * GetFrameTime();
	scrollingMid -= 5000.0f * GetFrameTime();
	scrollingFore -= 10000.0f * GetFrameTime();

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

	DrawText(TextFormat("V 0.4"), 5, 5, 10, RED);

	drawPlayer(player);

	if (isMultiplayer)
	{
		drawPlayer(player2);
	}
	for (int i = 0; i < maxLandEnemies + 1; i++)
	{
		if (landEnemies[i].isActive)
		{
			drawEnemy(landEnemies[i]);
		}
	}
	for (int i = 0; i < maxFlyingEnemies + 1; i++)
	{
		if (flyingEnemies[i].isActive)
		{
			drawEnemy(flyingEnemies[i]);
		}
	}
	drawPlayerBullets();

	DrawText(TextFormat("Lives %i", player.lives), 1, GetScreenHeight() - 30, 20, YELLOW);

	int scoreSize = MeasureText(TextFormat("Score %i", player.score),20);
	DrawText(TextFormat("Score %i", player.score),(GetScreenWidth() / 2) - (scoreSize / 2),0, 20, YELLOW);

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

		if (isMultiplayer)
		{
			if (player2.playerAmmo[i].isActive)
			{
				drawBullet(player2.playerAmmo[i]);
			}
		}
	}
}

void checkColitions()
{
	for (int i = 0; i < maxLandEnemies; i++)
	{
		if (landEnemies[i].isActive)
		{
			playerEnemyColition(landEnemies[i]);
		}
	}
	for (int i = 0; i < maxFlyingEnemies; i++)
	{
		if (flyingEnemies[i].isActive)
		{
			playerEnemyColition(flyingEnemies[i]);
		}
	}
	for (int i = 0; i < maxFlyingEnemies; i++)
	{
		if (flyingEnemies[i].isActive)
		{
			for (int j = 0; j < playerMaxAmmo; j++)
			{
				if (player.playerAmmo[j].isActive)
				{
					bulletEnemyColition(flyingEnemies[i],player.playerAmmo[j]);
				}

				if (isMultiplayer)
				{
					if (player2.playerAmmo[j].isActive)
					{
						bulletEnemyColition(flyingEnemies[i], player2.playerAmmo[j]);
					}
				}
			}
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
		if (!player.isHit)
		{
			player.lives--;
			player.isHit = true;
		}
	}
	if (isMultiplayer)
	{
		if (player2.pos.x > currentObstacle.pos.x + currentObstacle.widht || player2.pos.x + player2.widht < currentObstacle.pos.x || player2.pos.y > currentObstacle.pos.y + currentObstacle.height || player2.pos.y + player.height < currentObstacle.pos.y)
		{
			player2.playerColor = BLUE;
		}
		else
		{
			if (!player2.isHit)
			{
				player2.lives--;
				player2.isHit = true;
			}
		}
	}
	backToMenu = false;
}

void playerEnemyColition(Enemy& CurrentEnemy)
{
	if (player.pos.x > CurrentEnemy.pos.x + CurrentEnemy.widht || player.pos.x + player.widht < CurrentEnemy.pos.x || player.pos.y > CurrentEnemy.pos.y + CurrentEnemy.height || player.pos.y + player.height < CurrentEnemy.pos.y)
	{
		player.playerColor = GREEN;
	}
	else
	{
		if (!player.isHit)
		{
			player.lives --;
			player.isHit = true;
		}
	}

	if (isMultiplayer)
	{
		if (player2.pos.x > CurrentEnemy.pos.x + CurrentEnemy.widht || player2.pos.x + player2.widht < CurrentEnemy.pos.x || player2.pos.y > CurrentEnemy.pos.y + CurrentEnemy.height || player2.pos.y + player2.height < CurrentEnemy.pos.y)
		{
			player2.playerColor = BLUE;
		}
		else
		{
			if (!player2.isHit)
			{
				player2.lives--;
				player2.isHit = true;
			}
		}
	}
}

void bulletEnemyColition(Enemy& CurrentEnemy, Bullet& currentBullet)
{

	// temporary variables to set edges for testing
	float testX = currentBullet.position.x;
	float testY = currentBullet.position.y;

	// which edge is closest?
	if (currentBullet.position.x < CurrentEnemy.pos.x)
	{
		testX = CurrentEnemy.pos.x;      // test left edge
	}
	else if (currentBullet.position.x > CurrentEnemy.pos.x + CurrentEnemy.widht)
	{
		testX = CurrentEnemy.pos.x + CurrentEnemy.widht;   // right edge
	}

	if (currentBullet.position.y < CurrentEnemy.pos.y)
	{
		testY = CurrentEnemy.pos.y;      // top edge
	}
	else if (currentBullet.position.y > CurrentEnemy.pos.y + CurrentEnemy.height)
	{
		testY = CurrentEnemy.pos.y + CurrentEnemy.height;   // bottom edge
	}

	// get distance from closest edges
	float distX = currentBullet.position.x - testX;
	float distY = currentBullet.position.y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	if (distance <= currentBullet.rad)
	{
		CurrentEnemy.isActive = false;
		resetPosition(CurrentEnemy, flyingEnemiesCounter, false);
		currentBullet.isActive = false;
		player.score++;
	}
}

void checkOutOfBounds()
{
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

	if (isMultiplayer)
	{
		if (player2.pos.x <= 0)
		{
			player2.CurrentDirection = static_cast<float>(Directions::Stop);
		}
		if (player2.pos.x + (player2.widht) >= GetScreenWidth())
		{
			player2.CurrentDirection = static_cast<float>(Directions::Stop);
		}
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

		if (isMultiplayer)
		{
			if (player2.playerAmmo[i].position.y <= 0 && player2.playerAmmo[i].isActive)
			{
				player2.playerAmmo[i].isActive = false;
			}
		}
	}
}

void enemyOutOfBounds()
{
	for (int i = 0; i < maxLandEnemies; i++)
	{
		if (landEnemies[i].isActive && landEnemies[i].pos.x <= 0)
		{
			landEnemies[i].isActive = false;
			player.score++;
			if (isMultiplayer)
			{
				if (landEnemies[i].pos.y == static_cast<float>(GetScreenHeight()) - floorHeight2)
				{
					resetPosition(landEnemies[i], flyingEnemiesCounter, false);
				}
				else
				{
					resetPosition(landEnemies[i], flyingEnemiesCounter, true);
				}
			}
			else
			{
				resetPosition(landEnemies[i], flyingEnemiesCounter, false);
			}

			if (i == 0)
			{
				landEnemiesCounter = 0;
			}
			if (i == 1)
			{
				landEnemiesCounter = 1;
			}
			if (i == 2)
			{
				landEnemiesCounter = 2;
			}
		}
	}
	for (int i = 0; i < maxFlyingEnemies; i++)
	{
		if (flyingEnemies[i].isActive)
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