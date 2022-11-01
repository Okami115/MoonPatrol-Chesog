#include "button.h"



Button initButton(int initialPosX, int initialPosY, int fontSize, int buttonWidth, int buttonHeight, int optionNumber, string text, Color buttonColor, Color selectionColor)
{
	Button aux;
	aux.rect.x = static_cast<float>(initialPosX);
	aux.rect.y = static_cast<float>(initialPosY);
	aux.fontSize = fontSize;
	aux.rect.width = static_cast<float>(buttonWidth);
	aux.rect.height = static_cast<float>(buttonHeight);
	aux.optionNumber = optionNumber;
	aux.text = text;
	aux.buttonColor = buttonColor;
	aux.selectionColor = selectionColor;
	return aux;
}
void drawButton(Button actualButton)
{
	Vector2 mousePosition = { static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY()) };

	if (CheckCollisionPointRec(mousePosition, actualButton.rect))
	{
		DrawRectangle(static_cast<int>(actualButton.rect.x), static_cast<int>(actualButton.rect.y), static_cast<int>(actualButton.rect.width), static_cast<int>(actualButton.rect.height), actualButton.selectionColor);
	}
	else
	{
		DrawRectangle(static_cast<int>(actualButton.rect.x), static_cast<int>(actualButton.rect.y), static_cast<int>(actualButton.rect.width), static_cast<int>(actualButton.rect.height), actualButton.buttonColor);
	}
}
void drawButtonTexture(Button actualButton, Texture2D buttonTexture, Texture2D selectionTexture)
{
	float scale = 0.8f;

	Vector2 mousePosition = GetMousePosition();

	Rectangle sourRect = { 0,0,static_cast<float>(buttonTexture.width),static_cast<float>(buttonTexture.height) };
	Rectangle destRect = { actualButton.rect.x + actualButton.rect.width / 2 + buttonTexture.width / 8,actualButton.rect.y + actualButton.rect.height / 2,static_cast<float>(buttonTexture.width* scale),static_cast<float>(buttonTexture.height* scale) };
	Vector2 texturePiv = { static_cast<float>((buttonTexture.width) / 2),static_cast<float>((buttonTexture.height) / 2) };


	if (CheckCollisionPointRec(mousePosition, actualButton.rect))
	{
		DrawTexturePro(selectionTexture, sourRect, destRect, texturePiv, 5.0f, WHITE);
	}
	else
	{
		DrawTexturePro(buttonTexture, sourRect, destRect, texturePiv, 0, WHITE);
	}

}
void drawButtonTexture(Button actualButton, Texture2D buttonTexture, Texture2D selectionTexture, float scale)
{
	Vector2 mousePosition = GetMousePosition();

	Rectangle sourRect = { 0,0,static_cast<float>(buttonTexture.width),static_cast<float>(buttonTexture.height) };
	Rectangle destRect = { actualButton.rect.x + actualButton.rect.width / 2 + buttonTexture.width / 8,actualButton.rect.y + actualButton.rect.height / 2,static_cast<float>(buttonTexture.width* scale),static_cast<float>(buttonTexture.height* scale) };
	Vector2 texturePiv = { static_cast<float>((buttonTexture.width) / 2),static_cast<float>((buttonTexture.height) / 2) };


	if (CheckCollisionPointRec(mousePosition, actualButton.rect))
	{
		DrawTexturePro(selectionTexture, sourRect, destRect, texturePiv, 0, WHITE);
	}
	else
	{
		DrawTexturePro(buttonTexture, sourRect, destRect, texturePiv, 0, WHITE);
	}
}
