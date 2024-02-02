#ifndef WINDOW
#define WINDOW
#pragma once

#define UNICODE
#include <Windows.h>
#include <vector>
#include "Camera.h"
#include "Sprite.h"

class Window {
public:

	// Window Handles
	HANDLE consoleOutput;
	HANDLE consoleInput;
	HWND consoleWindow;

	Window(int winWidth, int winHeight, LPCWSTR winTitle);
	~Window();

	void OnUpdate();

	Camera* SetCamera(Camera* camera);
	Camera* GetCamera() { return activeCamera; }
	void SetTitle(LPCWSTR winTitle);
	// bool ShowMouseCursor(bool doShowCursor);
	// bool ShowConsoleCursor(bool doShowCursor);
	Sprite* NewSprite(std::wstring spriteName);
	Sprite* NewSprite(std::wstring spriteName, Texture spriteTexture);
	Sprite* GetSprite(unsigned int elementID);
	Sprite* GetSprite(std::wstring spriteName);
	unsigned short int GetWidth() { return width; }
	unsigned short int GetHeight() { return height; }

private:
	unsigned short int width, height;
	std::vector<Character> screenBuffer;
	std::vector<Sprite> sprites;
	Camera* activeCamera;

	// Window Properties
	LPCWSTR title = L"Game";
	COORD screenBufferPosition = { 0, 0 };
	COORD screenBufferSize = { (SHORT)width, (SHORT)height };
	SMALL_RECT windowSize = { 0, 0, (SHORT)width - 1, (SHORT)height - 1 };

	void DrawSprite(Sprite sprite);
	void DrawCharacter(Character character, Position pos);
	void DrawCharacterForeground(Character character, Position pos);
};

#endif // WINDOW
