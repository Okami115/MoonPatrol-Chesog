#include "Objets/Player/player.h"

Player initplayer() 
{
	Player aux;

	aux.widht = 50.0f;
	aux.height = 50.0f;
	aux.pos.x = static_cast<float>(aux.widht + aux.widht/2);
	aux.pos.y = static_cast<float>(GetScreenHeight() - aux.height / 2);
	aux.CurrentDirection = static_cast<float>(Directions::Down);
	aux.playerColor = GREEN;

	return aux;
}
void movePlayer(Player& player) 
{
	if (player.CurrentDirection == static_cast<float>(Directions::Down))
	{
		player.pos.y = static_cast<float>(GetScreenHeight() - (player.height + player.height / 4));
	}
	if (player.CurrentDirection == static_cast<float>(Directions::Up))
	{
		player.pos.y = static_cast<float>(GetScreenHeight() - ((player.height + player.height / 4))*2);
	}
}
void drawPlayer(Player player)
{
	DrawRectangle(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), static_cast<int>(player.widht), static_cast<int>(player.height),player.playerColor);
}