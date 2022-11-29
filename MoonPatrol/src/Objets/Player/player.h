#pragma once
#include "include/raylib.h"
#include "Objets/Bullet/bullet.h"
#include "GameManager/gameManager.h"

namespace MoonPatrol
{

	const int playerMaxAmmo = 100;

	struct Player
	{
		Vector2 pos;
		Color playerColor;

		float height;
		float widht;
		float CurrentDirection;
		float speed;

		int lives;
		int score;

		bool isHit;
		bool onAir;

		Bullet playerAmmo[playerMaxAmmo];
	};

	Player initplayer(bool isPlayer2);
	void shoot(Bullet& bullet, Player player);
	void movePlayer(Player& player, bool isPlayer2);
	void drawPlayer(Player player);
}