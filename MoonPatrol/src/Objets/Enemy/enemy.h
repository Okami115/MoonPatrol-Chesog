#pragma once
#include "include/raylib.h"
#include "GameManager/gameManager.h"

struct Enemy
{
	EnemyType enemyType;
	Color enemyColor;
	Vector2 pos;

	float height;
	float widht;
	float CurrentDirection;
	float speed;

	bool isAlctive;
};

Enemy initEnemy(EnemyType enemyType);
void drawEnemy(Enemy currentEnemy);
void moveEnemy(Enemy& currentEnemy);