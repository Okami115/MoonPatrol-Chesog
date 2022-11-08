#pragma once

enum class MenuStates { MainMenu,Gameplay,Rules,Options,Credits,Exit};
enum class Directions {Left,Right,Up,Down,Stop};
enum class EnemyType {Land,Flying};

const float floorHeight = 30.0f;
const float ceilingHeight = 30.0f;

const int maxLandEnemies = 3;
const int maxFlyingEnemies = 3;

void executeGame();