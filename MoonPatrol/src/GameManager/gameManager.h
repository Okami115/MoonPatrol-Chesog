#pragma once

enum class MenuStates { MainMenu,Gameplay,Rules,Options,Credits,Exit};
enum class Directions {Left,Right,Up,Down,Stop};
enum class EnemyType {Land,Flying};

const float floorHeight = 60.0f;
const float ceilingHeight = 60.0f;

const int maxLandEnemies = 3;
const int maxFlyingEnemies = 6;

void executeGame();