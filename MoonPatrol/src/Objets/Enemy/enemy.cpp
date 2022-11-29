#include "enemy.h"

namespace MoonPatrol
{

	Enemy initEnemy(EnemyType enemyType, bool isForPlayer2) 
	{
		Enemy aux = {};
		aux.enemyType = enemyType;
		aux.isActive = false;
		aux.isHit = false;

		if (aux.enemyType == EnemyType::Land)
		{
			aux.CurrentDirection.x = static_cast<float>(Directions::Left);
			aux.enemyColor = ORANGE;
			aux.speed = 200.0f;
			aux.height = 20.0f;
			aux.widht = 20.0f;
			aux.pos.x = static_cast<float>(GetScreenWidth());
			if (isForPlayer2)
			{
				aux.pos.y = static_cast<float>(GetScreenHeight()) - floorHeight2;
			}
			else
			{
				aux.pos.y = static_cast<float>(GetScreenHeight()) - floorHeight ;
			}
		}
		else if (aux.enemyType == EnemyType::Flying)
		{
			aux.CurrentDirection.x = static_cast<float>(Directions::Right);
			aux.CurrentDirection.y = static_cast<float>(Directions::Down);
			aux.enemyColor = YELLOW;
			aux.speed = 50.0f;
			aux.height = 20.0f;
			aux.widht = 20.0f;
			aux.pos.x = 0;
			aux.pos.y = ceilingHeight + aux.height / 2;
			aux.lives = 2;
		}
		return aux;
	}

	void resetPosition(Enemy& currentEnemy, int& cuerrentEnemyActives, bool isForPlayer2)
	{
		if (currentEnemy.enemyType == EnemyType::Land)
		{
			currentEnemy.pos.x = static_cast<float>(GetScreenWidth());
			if (isForPlayer2)
			{
				currentEnemy.pos.y = static_cast<float>(GetScreenHeight()) - floorHeight2;
			}
			else
			{
				currentEnemy.pos.y = static_cast<float>(GetScreenHeight()) - floorHeight;
			}
		}
		else if (currentEnemy.enemyType == EnemyType::Flying)
		{
			cuerrentEnemyActives--;
			currentEnemy.pos.x = 0;
			currentEnemy.pos.y = ceilingHeight + currentEnemy.height / 2;
		}
	}

	void drawEnemy(Enemy currentEnemy) 
	{
		DrawRectangle(static_cast<int>(currentEnemy.pos.x), static_cast<int>(currentEnemy.pos.y), static_cast<int>(currentEnemy.widht), static_cast<int>(currentEnemy.height), currentEnemy.enemyColor);
	}

	void moveEnemy(Enemy& currentEnemy)
	{
		int mov = 5;

		if (currentEnemy.CurrentDirection.x == static_cast<float>(Directions::Left))
		{
			currentEnemy.pos.x -= currentEnemy.speed * GetFrameTime();
		}
		if (currentEnemy.CurrentDirection.x == static_cast<float>(Directions::Right))
		{
			currentEnemy.pos.x += currentEnemy.speed * GetFrameTime();
		}

		if (currentEnemy.enemyType == EnemyType::Flying)
		{
			if (currentEnemy.CurrentDirection.y == static_cast<float>(Directions::Down))
			{
				currentEnemy.pos.y += sin(currentEnemy.speed * GetFrameTime()) * mov;
			}
			if (currentEnemy.CurrentDirection.y == static_cast<float>(Directions::Up))
			{
				currentEnemy.pos.y -= sin(currentEnemy.speed * GetFrameTime()) * mov;
			}
		}
	}
}