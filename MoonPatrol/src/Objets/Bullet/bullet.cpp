#include "bullet.h"

void initBullet(Bullet& currentBullet)
{

	currentBullet.position = { 0,0 };
	currentBullet.speed = { 500.0f,500.0f };
	currentBullet.rad = 4.0f;
	currentBullet.isActive = false;
	//currentBullet.bulletTexture = bulletTexture;
	currentBullet.color = LIME;

}
void drawBullet(Bullet bullet)
{
#if _DEBUG
	DrawCircle(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.rad, bullet.color);
	//Rectangle sourRect = { 0.0f,0.0f,static_cast<float>(bullet.bulletTexture.width),static_cast<float>(bullet.bulletTexture.height) };
//Rectangle destRect = { bullet.position.x,bullet.position.y,sourRect.width,sourRect.height };
//Vector2 texturePiv = { static_cast<float>(bullet.bulletTexture.width / 2),static_cast<float>(bullet.bulletTexture.height / 2) };
//
//DrawTexturePro(bullet.bulletTexture, sourRect, destRect, texturePiv, bullet.rotation + 90, WHITE);
#endif // _DEBUG
}
void moveBullet(Bullet& bullet)
{
	bullet.position.y -=  bullet.speed.y * GetFrameTime();
}