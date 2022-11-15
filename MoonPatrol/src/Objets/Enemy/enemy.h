#pragma once
#include <cmath>
#include "include/raylib.h"
#include "GameManager/gameManager.h"

struct Enemy
{
	EnemyType enemyType;
	Color enemyColor;
	Vector2 pos;
	Vector2 CurrentDirection;

	float height;
	float widht;
	float speed;

	int lives;

	bool isAlctive;
	bool isHit;
};

Enemy initEnemy(EnemyType enemyType);
void resetPosition(Enemy& currentEnemy);
void drawEnemy(Enemy currentEnemy);
void moveEnemy(Enemy& currentEnemy);