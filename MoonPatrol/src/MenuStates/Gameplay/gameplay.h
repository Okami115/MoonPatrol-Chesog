#pragma once
#include "include/raylib.h"
#include "Objets/Player/player.h"
#include "Objets/Obstacle/obstacle.h"


int gameplayLoop(bool& initGame, bool& backToMenu);
void updateGameplay(bool& backToMenu);
void moveParallax(); 
void drawGameplay();
void drawParallax();
void checkOutOfBounds();
void obstacleOutOfBounds(Obstacle& currentObstacle);
void checkColitions(bool& backToMenu);
void playerObstacleColition(Obstacle& currentObstacle, bool& backToMenu);
void loadTextures();
void unloadtextures();