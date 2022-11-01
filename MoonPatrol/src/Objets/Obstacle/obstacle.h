#pragma once
#include "include/raylib.h"
#include "GameManajer/gameManajer.h"

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