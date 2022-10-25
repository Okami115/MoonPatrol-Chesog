#include "Objets/Player/player.h"

Player initplayer() 
{
	Player aux;
	aux.pos.x = static_cast<float>(GetScreenWidth() / 2);
	aux.pos.y = static_cast<float>(GetScreenHeight() / 2);
	aux.widht = 50.0f;
	aux.height = 50.0f;
	aux.CurrentDirection = static_cast<float>(Directions::Down);
	aux.playerColor = GREEN;

	return aux;
}
void movePlayer(Player player) 
{
	if (player.CurrentDirection == static_cast<float>(Directions::Down))
	{
		player.pos.y = static_cast<float>(GetScreenHeight() / 2);
	}
	if (player.CurrentDirection == static_cast<float>(Directions::Up))
	{
		player.pos.y = static_cast<float>((GetScreenHeight() / 2) + player.height * 2);
	}
}
void drawPlayer(Player player)
{
	DrawRectangle(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), static_cast<int>(player.widht), static_cast<int>(player.height),player.playerColor);
}