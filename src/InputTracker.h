#ifndef INPUTTRACKER_H
#define INPUTTRACKER_H
#pragma once

#include <Windows.h>
#include <set>
#include <assert.h>
#include "Position.h"
#include "Window.h"

class InputTracker {
public:
	Window* window;
	BYTE keys[256];
	BYTE lastKeys[256];

	InputTracker();
	~InputTracker();

	void OnUpdate();

	bool IsKeyPressed(int virtualKey);
	bool IsKeyReleased(int virtualKey);
	bool IsKeyDown(int virtualKey);
	bool IsKeyUp(int virtualKey);
	Position GetMouseToWindow();
	Position GetMouseToWorld();

private:
	Position mousePos;
};

#endif // INPUT_H