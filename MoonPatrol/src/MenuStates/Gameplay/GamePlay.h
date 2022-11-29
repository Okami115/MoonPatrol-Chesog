#pragma once
#include "include/raylib.h"
#include "Objets/Player/player.h"
#include "Objets/Obstacle/obstacle.h"
#include "Objets/Enemy/enemy.h"

namespace MoonPatrol
{
	int gameplayLoop(bool& initGame, bool& backToMenu);

	void updateGameplay(bool& backToMenu);

	void moveParallax(); 

	void drawGameplay();

	void drawParallax();

	void checkOutOfBounds();

	void obstacleOutOfBounds(Obstacle& currentObstacle);

	void checkColitions();

	void playerObstacleColition(Obstacle& currentObstacle, bool& backToMenu);

	void loadTextures();

	void unloadtextures();

	void drawPlayerBullets();

	void checkInput();

	void playerOutOfBounds();

	void enemyOutOfBounds();

	void playerEnemyColition(Enemy& CurrentEnemy);

	void bulletEnemyColition(Enemy& CurrentEnemy, Bullet& currentBullet);

}