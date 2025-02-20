#include "mainMenu.h"

namespace MoonPatrol
{
	static Button button1;
	static Button button2;
	static Button button3;
	static Button button4;
	static Button button5;
	static Button button6;

	extern int highScore;

	Texture MenuBackground;
	Texture CreditsBackground;
	Texture RulesBackground;
	Texture OptionsBackground;

	Music MenuMusic;
	Music GameMusic;

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

		button1 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) - buttonHeight * 2, fontSize, buttonWidth, buttonHeight, static_cast<int>(MenuStates::Game), "SinglePlayer", GREEN, RED);
		button2 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 0, fontSize, buttonWidth, buttonHeight, static_cast<int>(MenuStates::MultiPlayer), "MultiPlayer", GREEN, RED);
		button3 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 2, fontSize, buttonWidth, buttonHeight, static_cast<int>(MenuStates::Rules), "Reglas", GREEN, RED);
		button4 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 4, fontSize, buttonWidth, buttonHeight, static_cast<int>(MenuStates::Options), "Opciones", GREEN, RED);
		button5 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 6, fontSize, buttonWidth, buttonHeight, static_cast<int>(MenuStates::Credits), "Creditos", GREEN, RED);
		button6 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 8, fontSize, buttonWidth, buttonHeight, static_cast<int>(MenuStates::Exit), "Salir", GREEN, RED);
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
	void drawMenu(int screenWidth, int screenHeight,int& point)
	{
		int textSizeButton1 = MeasureText(TextFormat("SinglePlayer"), button1.fontSize);
		int textSizeButton2 = MeasureText(TextFormat("MultiPlayer"), button2.fontSize);
		int textSizeButton3 = MeasureText(TextFormat("REGLAS"), button3.fontSize);
		int textSizeButton4 = MeasureText(TextFormat("OPCIONES"), button4.fontSize);
		int textSizeButton5 = MeasureText(TextFormat("CREDITOS"), button5.fontSize);
		int textSizeButton6 = MeasureText(TextFormat("SALIR"), button6.fontSize);

		ClearBackground(BLACK);

		DrawTexture(MenuBackground, 0, 0, WHITE);
		DrawText("V1.0", 5, 5, 10, RED);

		if (point == static_cast<int>(MenuStates::Game))
		{
			DrawRectangle(static_cast<int>(button1.rect.x), static_cast<int>(button1.rect.y), static_cast<int>(button1.rect.width), static_cast<int>(button1.rect.height),button1.buttonColor);
		}
		else if (point != static_cast<int>(MenuStates::Game))
		{
			DrawRectangle(static_cast<int>(button1.rect.x), static_cast<int>(button1.rect.y), static_cast<int>(button1.rect.width), static_cast<int>(button1.rect.height), button1.selectionColor);
		}
		DrawText("SinglePlayer", ((screenWidth / 2) - (textSizeButton1 / 2)), static_cast<int>(button1.rect.y + button1.rect.height / 6), button1.fontSize, BLACK);

		if (point == static_cast<int>(MenuStates::MultiPlayer))
		{
			DrawRectangle(static_cast<int>(button2.rect.x), static_cast<int>(button2.rect.y), static_cast<int>(button2.rect.width), static_cast<int>(button2.rect.height), button2.buttonColor);
		}
		else if (point != static_cast<int>(MenuStates::MultiPlayer))
		{
			DrawRectangle(static_cast<int>(button2.rect.x), static_cast<int>(button2.rect.y), static_cast<int>(button2.rect.width), static_cast<int>(button2.rect.height), button2.selectionColor);
		}
		DrawText("MultiPlayer", ((screenWidth / 2) - (textSizeButton2 / 2)), static_cast<int>(button2.rect.y + button2.rect.height / 6), button2.fontSize, BLACK);

		if (point == static_cast<int>(MenuStates::Rules))
		{
			DrawRectangle(static_cast<int>(button3.rect.x), static_cast<int>(button3.rect.y), static_cast<int>(button3.rect.width), static_cast<int>(button3.rect.height), button3.buttonColor);
		}
		else if (point != static_cast<int>(MenuStates::Rules))
		{
			DrawRectangle(static_cast<int>(button3.rect.x), static_cast<int>(button3.rect.y), static_cast<int>(button3.rect.width), static_cast<int>(button3.rect.height), button3.selectionColor);
		}
		DrawText("REGLAS", ((screenWidth / 2) - (textSizeButton3 / 2)), static_cast<int>(button3.rect.y + button3.rect.height / 6), button3.fontSize, BLACK);

		if (point == static_cast<int>(MenuStates::Options))
		{
			DrawRectangle(static_cast<int>(button4.rect.x), static_cast<int>(button4.rect.y), static_cast<int>(button4.rect.width), static_cast<int>(button4.rect.height), button4.buttonColor);
		}
		else if (point != static_cast<int>(MenuStates::Options))
		{
			DrawRectangle(static_cast<int>(button4.rect.x), static_cast<int>(button4.rect.y), static_cast<int>(button4.rect.width), static_cast<int>(button4.rect.height),button4.selectionColor);
		}
		DrawText("OPCIONES", ((screenWidth / 2) - (textSizeButton4 / 2)), static_cast<int>(button4.rect.y + button4.rect.height / 6), button4.fontSize, BLACK);

		if (point == static_cast<int>(MenuStates::Credits))
		{
			DrawRectangle(static_cast<int>(button5.rect.x), static_cast<int>(button5.rect.y), static_cast<int>(button5.rect.width), static_cast<int>(button5.rect.height), button5.buttonColor);
		}
		else if (point != static_cast<int>(MenuStates::Credits))
		{
			DrawRectangle(static_cast<int>(button5.rect.x), static_cast<int>(button5.rect.y), static_cast<int>(button5.rect.width), static_cast<int>(button5.rect.height), button5.selectionColor);
		}
		DrawText("CREDITOS", ((screenWidth / 2) - (textSizeButton5 / 2)), static_cast<int>(button5.rect.y + button5.rect.height / 6), button5.fontSize, BLACK);

		if (point == static_cast<int>(MenuStates::Exit))
		{
			DrawRectangle(static_cast<int>(button6.rect.x), static_cast<int>(button6.rect.y), static_cast<int>(button6.rect.width), static_cast<int>(button6.rect.height), button6.buttonColor);
		}
		else if (point != static_cast<int>(MenuStates::Exit))
		{
			DrawRectangle(static_cast<int>(button6.rect.x), static_cast<int>(button6.rect.y), static_cast<int>(button6.rect.width), static_cast<int>(button6.rect.height), button6.selectionColor);
		}
		DrawText("SALIR", ((screenWidth / 2) - (textSizeButton6 / 2)), static_cast<int>(button6.rect.y + button6.rect.height / 6), button6.fontSize, BLACK);

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

	int checkInput(int& point)
	{
		int defaultOption = 0;
		if (IsKeyReleased(KeyboardKey(KEY_UP)))
		{
			if (point <= static_cast<int>(MenuStates::Game))
			{
				point = static_cast<int>(MenuStates::Exit);
			}
			else
			{
				point--;
			}
			return defaultOption;
		}
		else if (IsKeyReleased(KeyboardKey(KEY_DOWN)))
		{
			if (point >= static_cast<int>(MenuStates::Exit))
			{
				point = static_cast<int>(MenuStates::Game);
			}
			else
			{
				point++;
			}
			return defaultOption;
		}
		else if (IsKeyReleased(KeyboardKey(KEY_ENTER)))
		{
			return point;
		}
		else if (IsKeyReleased(KEY_ESCAPE))
		{
			return static_cast<int>(MenuStates::Exit);
		}
		else
		{
			return defaultOption;
		}
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
		else if (CheckCollisionPointRec(mousePosition, button6.rect))
		{
			point = button6.optionNumber;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				return button6.optionNumber;
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

	int Credits(int& point)
	{
		if (IsKeyReleased(KEY_ESCAPE))
		{
			point = static_cast<int>(MenuStates::MainMenu);
		}
		ClearBackground(BLACK);
		BeginDrawing();
		drawCredits();
		EndDrawing();
		return point;
	}
	void drawCredits()
	{
		DrawTexture(CreditsBackground, 0, 0, WHITE);
	}

	int Rules(int& point)
	{
		if (IsKeyReleased(KEY_ESCAPE))
		{
			point = static_cast<int>(MenuStates::MainMenu);
		}
		ClearBackground(BLACK);
		BeginDrawing();
		drawRules();
		EndDrawing();
		return point;
	}
	void drawRules()
	{
		DrawTexture(RulesBackground, 0, 0, WHITE);
	}

	int Options(int& point)
	{
		if (IsKeyReleased(KEY_ESCAPE))
		{
			point = static_cast<int>(MenuStates::MainMenu);
		}
		ClearBackground(BLACK);
		BeginDrawing();
		drawOptions();
		EndDrawing();
		return point;
	}
	void drawOptions()
	{
		DrawTexture(OptionsBackground, 0, 0, WHITE);
	}

	void playMusic(int point)
	{
		if (point == static_cast<int>(MenuStates::Game))
		{
			StopMusicStream(MenuMusic);
			PlayMusicStream(GameMusic);
		}
		else
		{
			StopMusicStream(GameMusic);
			PlayMusicStream(MenuMusic);
		}

		UpdateMusicStream(GameMusic);
		UpdateMusicStream(MenuMusic);
		SetMusicVolume(GameMusic, 0.3f);
		SetMusicVolume(MenuMusic, 0.3f);
	}


	void initTexturesAndMusic()
	{
		MenuBackground = LoadTexture("res/Menu.png");
		CreditsBackground = LoadTexture("res/Credits.png");
		RulesBackground = LoadTexture("res/Rules.png");
		OptionsBackground = LoadTexture("res/Options.png");

		MenuMusic = LoadMusicStream("res/Menu Music.wav");
		GameMusic = LoadMusicStream("res/Game Music.wav");
	}

	void UninitTexturesAndMusic()
	{
		UnloadTexture(MenuBackground);
		UnloadTexture(CreditsBackground);
		UnloadTexture(RulesBackground);
		UnloadTexture(OptionsBackground);

		UnloadMusicStream(MenuMusic);
		UnloadMusicStream(GameMusic);
	}

}