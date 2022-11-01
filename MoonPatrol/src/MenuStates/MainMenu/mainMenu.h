#pragma once
#include "include/raylib.h"
#include "Objets/Button/button.h"
#include "GameManager/gameManager.h"


void drawMenu(int screenWidth, int screenHeight, int& point);
int checkInput(int& point);
int mainMenu(int& point);
int checkMouseColition(Vector2 mousePosition, int& point);

