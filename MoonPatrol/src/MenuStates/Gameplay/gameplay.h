#pragma once
#include "include/raylib.h"
#include "Objets/Player/player.h"
#include "Objets/Obstacle/obstacle.h"


int gameplayLoop(bool& initGame, bool backToMenu);
void updateGameplay();
void moveParallax(); 
void drawGameplay();
void drawParallax();
void checkOutOfBounds();
void obstacleOutOfBounds(Obstacle& currentObstacle);
void checkColitions();
void playerObstacleColition(Obstacle& currentObstacle);
void loadTextures();
void unloadtextures();