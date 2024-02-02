#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#define NOMINMAX
#include "Int2D.h"
#include <Windows.h>
#include "Texture.h"

class Window {
private:
	Texture screenBuffer;
	LPCWSTR title;

	COORD screenBufferPosition = { 0, 0 };
	COORD screenBufferSize = { (SHORT)screenBuffer.GetWidth(), (SHORT)screenBuffer.GetHeight() };
	SMALL_RECT windowSize = { 0, 0, (SHORT)screenBuffer.GetWidth() - 1, (SHORT)screenBuffer.GetHeight() - 1 };
public:

	// Window Handles
	HANDLE consoleOutput;
	HANDLE consoleInput;
	HWND consoleWindow;

	Window(Int2D windowDimensions = Int2D(120, 30), LPCWSTR windowTitle = L"Unicode Game");

	void Update();

	LPCWSTR GetTitle() { return title; }
	LPCWSTR SetTitle(LPCWSTR newTitle);
};

#endif // WINDOW_H