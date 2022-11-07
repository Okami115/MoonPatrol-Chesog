#pragma once
#include "include/raylib.h"

struct Enemy
{
	Vector2 pos;
	Color enemyColor;
	float height;
	float widht;
	float CurrentDirection;
};