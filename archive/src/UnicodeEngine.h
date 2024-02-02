#ifndef UNICODEENGINE_H
#define UNICODEENGINE_H
#pragma once

#include "Int2D.h"
#include "Scene.h"
#include "Window.h"

class UnicodeEngine {
public:
	Scene activeScene;
	Window activeWindow;

	UnicodeEngine();
	UnicodeEngine(Int2D windowDimensions);
	UnicodeEngine(Int2D windowDimensions, LPCWSTR windowName);

	void Update();
};

#endif // UNICODEENGINE_H