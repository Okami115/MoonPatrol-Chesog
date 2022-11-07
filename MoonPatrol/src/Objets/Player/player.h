#pragma once
#include "include/raylib.h"
#include "Objets/Bullet/bullet.h"
#include "GameManager/gameManager.h"

const int playerMaxAmmo = 100;

struct Player
{
	Vector2 pos;
	Color playerColor;
	float height;
	float widht;
	float CurrentDirection;
	Bullet playerAmmo[playerMaxAmmo];
};

Player initplayer();
void shoot(Bullet& bullet, Player player);
void movePlayer(Player& player);
void drawPlayer(Player player);