#include "Objets/Player/player.h"

extern float gravity;

Player initplayer() 
{
	Player aux;

	aux.widht = 50.0f;
	aux.height = 20.0f;
	aux.pos.x = aux.widht;
	aux.pos.y = (floorHeight - aux.height / 2);
	aux.CurrentDirection = static_cast<float>(Directions::Down);
	aux.playerColor = GREEN;
	aux.speed = 200.0f;

	for (int i = 0; i < playerMaxAmmo; i++)
	{
		initBullet(aux.playerAmmo[i]);
	}

	return aux;
}
void shoot(Bullet& bullet, Player player)
{
	//PlaySound(shotSound);

	bullet.position.x = player.pos.x;
	bullet.position.y = player.pos.y;
	bullet.trayectory.y += 100.0f * GetFrameTime();

	bullet.isActive = true;
	//bullet.rotation = player.rotation;
}
void movePlayer(Player& player) 
{
	player.pos.y = player.pos.y + gravity * GetFrameTime();

	if (player.pos.y > static_cast<float>(GetScreenHeight() - (player.height + player.height / 2)))
	{
		player.pos.y = static_cast<float>(GetScreenHeight() - (player.height + player.height / 2));
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