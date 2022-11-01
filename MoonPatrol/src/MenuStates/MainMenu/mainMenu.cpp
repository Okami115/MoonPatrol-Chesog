#include "mainMenu.h"


static Button button1;
static Button button2;
static Button button3;
static Button button4;
static Button button5;

extern int highScore;

int mainMenu(int& point)
{
	ShowCursor();
	int fontSize = 30;
	int buttonWidth = 300;
	int buttonHeight = 40;
	int selection = 0;
	int selection2 = 0;
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	button1 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2), fontSize, buttonWidth, buttonHeight, (int)MenuStates::Gameplay, "Jugar", GREEN, RED);
	button2 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 2, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Rules, "Reglas", GREEN, RED);
	button3 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 4, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Options, "Opciones", GREEN, RED);
	button4 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 6, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Credits, "Creditos", GREEN, RED);
	button5 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 8, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Exit, "Salir", GREEN, RED);
	Vector2 mousePosition = GetMousePosition();

	selection = checkInput(point);
	selection2 = checkMouseColition(mousePosition, point);

	BeginDrawing();
	drawMenu(screenWidth, screenHeight,point);
	EndDrawing();

	if (selection != 0)
	{
		return selection;
	}
	else
	{
		return selection2;
	}
}
int checkInput(int& point)
{
	int defaultOption = 0;
	if (IsKeyDown(KeyboardKey(KEY_UP)))
	{
		if (point <= (int)MenuStates::Gameplay)
		{
			point = (int)MenuStates::Exit;
		}
		else
		{
			point--;
		}
		return defaultOption;
	}
	else if (IsKeyDown(KeyboardKey(KEY_DOWN)))
	{
		if (point >= (int)MenuStates::Exit)
		{
			point = (int)MenuStates::Gameplay;
		}
		else
		{
			point++;
		}
		return defaultOption;
	}
	else if (IsKeyDown(KeyboardKey(KEY_ENTER)))
	{
		return point;
	}
	else if (IsKeyDown(KEY_ESCAPE))
	{
		return (int)MenuStates::Exit;
	}
	else
	{
		return defaultOption;
	}
}
void drawMenu(int screenWidth, int screenHeight,int& point)
{
	int fontSize = 80;
	int textSizeTitle = MeasureText(TextFormat("Moon Lander"), fontSize);
	int textSizeButton1 = MeasureText(TextFormat("JUGAR"), button1.fontSize);
	int textSizeButton2 = MeasureText(TextFormat("REGLAS"), button2.fontSize);
	int textSizeButton3 = MeasureText(TextFormat("OPCIONES"), button3.fontSize);
	int textSizeButton4 = MeasureText(TextFormat("CREDITOS"), button4.fontSize);
	int textSizeButton5 = MeasureText(TextFormat("SALIR"), button5.fontSize);

	ClearBackground(BLACK);

	DrawText("Moon Lander", (screenWidth / 2) - (textSizeTitle / 2), fontSize, fontSize, RED);

	if (point == (int)MenuStates::Gameplay)
	{
		DrawRectangle(static_cast<int>(button1.rect.x), static_cast<int>(button1.rect.y), static_cast<int>(button1.rect.width), static_cast<int>(button1.rect.height),button1.buttonColor);
	}
	else if (point != (int)MenuStates::Gameplay)
	{
		DrawRectangle(static_cast<int>(button1.rect.x), static_cast<int>(button1.rect.y), static_cast<int>(button1.rect.width), static_cast<int>(button1.rect.height), button1.selectionColor);
	}
	DrawText("JUGAR", ((screenWidth / 2) - (textSizeButton1 / 2)), static_cast<int>(button1.rect.y + button1.rect.height / 6), button1.fontSize, BLACK);

	if (point == (int)MenuStates::Rules)
	{
		DrawRectangle(static_cast<int>(button2.rect.x), static_cast<int>(button2.rect.y), static_cast<int>(button2.rect.width), static_cast<int>(button2.rect.height), button2.buttonColor);
	}
	else if (point != (int)MenuStates::Rules)
	{
		DrawRectangle(static_cast<int>(button2.rect.x), static_cast<int>(button2.rect.y), static_cast<int>(button2.rect.width), static_cast<int>(button2.rect.height), button2.selectionColor);
	}
	DrawText("REGLAS", ((screenWidth / 2) - (textSizeButton2 / 2)), static_cast<int>(button2.rect.y + button2.rect.height / 6), button2.fontSize, BLACK);

	if (point == (int)MenuStates::Options)
	{
		DrawRectangle(static_cast<int>(button3.rect.x), static_cast<int>(button3.rect.y), static_cast<int>(button3.rect.width), static_cast<int>(button3.rect.height), button3.buttonColor);
	}
	else if (point != (int)MenuStates::Options)
	{
		DrawRectangle(static_cast<int>(button3.rect.x), static_cast<int>(button3.rect.y), static_cast<int>(button3.rect.width), static_cast<int>(button3.rect.height),button3.selectionColor);
	}
	DrawText("OPCIONES", ((screenWidth / 2) - (textSizeButton3 / 2)), static_cast<int>(button3.rect.y + button3.rect.height / 6), button3.fontSize, BLACK);

	if (point == (int)MenuStates::Credits)
	{
		DrawRectangle(static_cast<int>(button4.rect.x), static_cast<int>(button4.rect.y), static_cast<int>(button4.rect.width), static_cast<int>(button4.rect.height), button4.buttonColor);
	}
	else if (point != (int)MenuStates::Credits)
	{
		DrawRectangle(static_cast<int>(button4.rect.x), static_cast<int>(button4.rect.y), static_cast<int>(button4.rect.width), static_cast<int>(button4.rect.height), button4.selectionColor);
	}
	DrawText("CREDITOS", ((screenWidth / 2) - (textSizeButton4 / 2)), static_cast<int>(button4.rect.y + button4.rect.height / 6), button4.fontSize, BLACK);

	if (point == (int)MenuStates::Exit)
	{
		DrawRectangle(static_cast<int>(button5.rect.x), static_cast<int>(button5.rect.y), static_cast<int>(button5.rect.width), static_cast<int>(button5.rect.height), button5.buttonColor);
	}
	else if (point != (int)MenuStates::Exit)
	{
		DrawRectangle(static_cast<int>(button5.rect.x), static_cast<int>(button5.rect.y), static_cast<int>(button5.rect.width), static_cast<int>(button5.rect.height), button5.selectionColor);
	}
	DrawText("SALIR", ((screenWidth / 2) - (textSizeButton5 / 2)), static_cast<int>(button5.rect.y + button5.rect.height / 6), button5.fontSize, BLACK);

#ifdef _DEBUG
	DrawRectangle(0, screenHeight / 2, screenWidth, 1, DARKGREEN);
	DrawRectangle(0, static_cast<int>(button1.rect.y + button1.rect.height / 2), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>(button2.rect.y + button2.rect.height / 2), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>(button3.rect.y + button3.rect.height / 2), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>(button4.rect.y + button4.rect.height / 2), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>(button5.rect.y + button5.rect.height / 2), screenWidth, 1, BLUE);
	DrawRectangle(screenWidth / 2, 0, 1, screenHeight, DARKGREEN);
#endif // DEBUG
}
int checkMouseColition(Vector2 mousePosition, int& point)
{
	if (CheckCollisionPointRec(mousePosition, button1.rect))
	{
		point = button1.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button1.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else if (CheckCollisionPointRec(mousePosition, button2.rect))
	{
		point = button2.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button2.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else if (CheckCollisionPointRec(mousePosition, button3.rect))
	{
		point = button3.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button3.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else if (CheckCollisionPointRec(mousePosition, button4.rect))
	{
		point = button4.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button4.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else if (CheckCollisionPointRec(mousePosition, button5.rect))
	{
		point = button5.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button5.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
