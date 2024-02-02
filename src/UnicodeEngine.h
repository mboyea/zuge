#ifndef UNICODEENGINE
#define UNICODEENGINE
#pragma once

#include "Scene.h"
#include "Window.h"
#include "InputTracker.h"
#include "TimeTracker.h"
#include "Random.h"

// Built-in Scripts

class UnicodeEngine {
public:
	Scene* activeScene;
	Window* activeWindow;
	InputTracker input;
	TimeTracker time;
	
	UnicodeEngine(Scene* scene, Window* window);
	~UnicodeEngine();

	void Update();
};

#endif // UNICODEENGINE
