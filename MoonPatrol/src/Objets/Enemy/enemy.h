#pragma once
#include <cmath>
#include "include/raylib.h"
#include "GameManager/gameManager.h"

namespace MoonPatrol
{
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

		bool isActive;
		bool isHit;
	};

	Enemy initEnemy(EnemyType enemyType, bool isForPlayer2);
	void resetPosition(Enemy& currentEnemy, int& cuerrentEnemyActives, bool isForPlayer2);
	void drawEnemy(Enemy currentEnemy);
	void moveEnemy(Enemy& currentEnemy);

}