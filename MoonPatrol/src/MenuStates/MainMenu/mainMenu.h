#pragma once
#include "include/raylib.h"
#include "Objets/Button/button.h"
#include "GameManager/gameManager.h"


int mainMenu(int& point);
void drawMenu(int screenWidth, int screenHeight, int& point);

int Credits(int& point);
void drawCredits();

int Rules(int& point);
void drawRules();

int Options(int& point);
void drawOptions();

int checkInput(int& point);
int checkMouseColition(Vector2 mousePosition, int& point);

void initTextures();