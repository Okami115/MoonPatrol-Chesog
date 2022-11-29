#pragma once


namespace MoonPatrol
{

	enum class MenuStates { MainMenu,Game,MultiPlayer,Rules,Options,Credits,Exit};
	enum class Directions {Left,Right,Up,Down,Stop};
	enum class EnemyType {Land,Flying};

	const float floorHeight = 60.0f;
	const float floorHeight2 = 160.0f;
	const float ceilingHeight = 60.0f;

	const int maxLandEnemies = 6;
	const int maxFlyingEnemies = 6;

	void executeGame();
}