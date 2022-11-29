#include "obstacle.h"

namespace MoonPatrol
{

	Obstacle initObstacle() 
	{
		Obstacle aux;

		aux.widht = 20.0f;
		aux.height = 20.0f;
		aux.pos.x = static_cast<float>(GetScreenWidth() - aux.widht);
		aux.pos.y = static_cast<float>(GetScreenHeight() - aux.height * 2);
		aux.CurrentDirection = static_cast<float>(Directions::Left);
		aux.obstacleColor = RED;

		return aux;
	}
	void moveObstacle(Obstacle& currentObstacle) 
	{
		if (currentObstacle.CurrentDirection == static_cast<float>(Directions::Left))
		{
			currentObstacle.pos.x -= 100.0f * GetFrameTime();
		}
	}
	void drawObstacle(Obstacle currentObstacle)
	{
		DrawRectangle(static_cast<int>(currentObstacle.pos.x), static_cast<int>(currentObstacle.pos.y), static_cast<int>(currentObstacle.widht), static_cast<int>(currentObstacle.height), currentObstacle.obstacleColor);
	}
}