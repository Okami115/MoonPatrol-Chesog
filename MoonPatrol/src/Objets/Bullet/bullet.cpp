#include "bullet.h"

void initBullet(Bullet& currentBullet)
{

	currentBullet.position = { -10,-10 };
	currentBullet.speed = { 500.0f,500.0f };
	currentBullet.rad = 4.0f;
	currentBullet.isActive = false;
	currentBullet.color = VIOLET;

}

void drawBullet(Bullet bullet)
{
	DrawCircle(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.rad, bullet.color);
}
void moveBullet(Bullet& bullet)
{
	bullet.position.y -=  bullet.speed.y * GetFrameTime();

	if (bullet.position.y < 0)
	{
		bullet.position = { -10,-10 };
	}
}