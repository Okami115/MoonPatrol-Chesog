#include "Objets/Player/player.h"

extern float gravity;

Player initplayer() 
{
	Player aux;

	aux.widht = 50.0f;
	aux.height = 20.0f;
	aux.pos.x = aux.widht;
	aux.pos.y = static_cast<float>(GetScreenHeight()) - floorHeight;
	aux.CurrentDirection = static_cast<float>(Directions::Down);
	aux.playerColor = GREEN;
	aux.speed = 200.0f;
	aux.lives = 1;
	aux.score = 0;
	aux.isHit = false;
	aux.onAir = false;

	for (int i = 0; i < playerMaxAmmo; i++)
	{
		initBullet(aux.playerAmmo[i]);
	}

	return aux;
}
void shoot(Bullet& bullet, Player player)
{
	//PlaySound(shotSound);

	bullet.position.x = player.pos.x + (player.widht / 2);
	bullet.position.y = player.pos.y + (player.height / 2);
	bullet.trayectory.y += 100.0f * GetFrameTime();
	bullet.isActive = true;
	

	//bullet.rotation = player.rotation;
}
void movePlayer(Player& player) 
{
	player.pos.y = player.pos.y + gravity * GetFrameTime();

	if (player.pos.y > static_cast<float>(GetScreenHeight()) - floorHeight)
	{
		player.pos.y = static_cast<float>(GetScreenHeight()) - floorHeight;
	}
	if (player.CurrentDirection == static_cast<float>(Directions::Left))
	{
		player.pos.x -= player.speed * GetFrameTime();
	}
	if (player.CurrentDirection == static_cast<float>(Directions::Right))
	{
		player.pos.x += player.speed * GetFrameTime();
	}
	if (player.CurrentDirection == static_cast<float>(Directions::Stop))
	{
		player.pos.x;
	}
}
void drawPlayer(Player player)
{
	DrawRectangle(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), static_cast<int>(player.widht), static_cast<int>(player.height),player.playerColor);
}