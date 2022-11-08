#include "enemy.h"

Enemy initEnemy(EnemyType enemyType) 
{
	Enemy aux;
	aux.enemyType = enemyType;
	aux.speed = 200.0f;
	aux.isAlctive = false;

	if (aux.enemyType == EnemyType::Land)
	{
		aux.CurrentDirection = static_cast<float>(Directions::Left);
		aux.enemyColor = ORANGE;
		aux.height = 20.0f;
		aux.widht = 20.0f;
		aux.pos.x = GetScreenWidth();
		aux.pos.y = floorHeight - aux.height / 2;
	}
	else if (aux.enemyType == EnemyType::Flying)
	{
		aux.CurrentDirection = static_cast<float>(Directions::Right);
		aux.enemyColor = YELLOW;
		aux.height = 20.0f;
		aux.widht = 20.0f;
		aux.pos.x = 0;
		aux.pos.y = ceilingHeight + aux.height / 2;
	}
}

void drawEnemy(Enemy currentEnemy) 
{
	DrawRectangle(static_cast<int>(currentEnemy.pos.x), static_cast<int>(currentEnemy.pos.y), static_cast<int>(currentEnemy.widht), static_cast<int>(currentEnemy.height), currentEnemy.enemyColor);
}

void moveEnemy(Enemy& currentEnemy)
{
	if (currentEnemy.CurrentDirection == static_cast<float>(Directions::Left))
	{
		currentEnemy.pos.x -= currentEnemy.speed * GetFrameTime();
	}
	if (currentEnemy.CurrentDirection == static_cast<float>(Directions::Right))
	{
		currentEnemy.pos.x += currentEnemy.speed * GetFrameTime();
	}

	if (currentEnemy.enemyType == EnemyType::Flying)
	{
		if (currentEnemy.pos.y <= ceilingHeight + currentEnemy.height / 2)
		{
			currentEnemy.pos.y += currentEnemy.speed * GetFrameTime();
		}
		if (currentEnemy.pos.y >= ceilingHeight * 2)
		{
			currentEnemy.pos.y -= currentEnemy.speed * GetFrameTime();
		}
	}
}