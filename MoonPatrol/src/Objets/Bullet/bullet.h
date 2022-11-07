#pragma once
#include "include/raylib.h"

struct Bullet
{
	Vector2 position;
	Vector2 trayectory;
	Vector2 speed;
	float rad;
	float rotation;
	bool isActive;
	Color color;
	Texture2D bulletTexture;
};
void initBullet(Bullet& currentBullet);
void drawBullet(Bullet bullet);
void moveBullet(Bullet& bullet);