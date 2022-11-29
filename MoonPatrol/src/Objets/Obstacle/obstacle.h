#pragma once
#include "include/raylib.h"
#include "GameManager/gameManager.h"

namespace MoonPatrol
{
	struct Obstacle
	{
		Vector2 pos;
		Color obstacleColor;
		float height;
		float widht;
		float CurrentDirection;
	};

	Obstacle initObstacle();
	void moveObstacle(Obstacle& currentObstacle);
	void drawObstacle(Obstacle currentObstacle);

}