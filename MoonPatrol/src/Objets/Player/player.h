#pragma once
#include "include/raylib.h"
#include "GameManager/gameManager.h"

struct Player
{
	Vector2 pos;
	Color playerColor;
	float height;
	float widht;
	float CurrentDirection;
};

Player initplayer();
void movePlayer(Player& player);
void drawPlayer(Player player);