#pragma once
#include "include/raylib.h"
#include "GameManajer/gameManajer.h"

struct Player
{
	Vector2 pos;
	float height;
	float widht;
	Color playerColor;
	float CurrentDirection;
};

Player initplayer();
void movePlayer(Player& player);
void drawPlayer(Player player);