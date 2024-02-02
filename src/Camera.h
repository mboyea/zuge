#ifndef CAMERA
#define CAMERA
#pragma once

#include "Position.h"
#include "Pivot.h"
#include "Sprite.h"
#include <Windows.h>
#include <vector>

class Camera {
public:
	int width, height;
	Position position = Position(1, 1);
	Pivot pivot = Pivot::BottomLeft;

	std::vector<Character> screenBuffer;
	std::vector<Sprite>* renderList;

	Camera(int viewWidth, int viewHeight);
	Camera(int viewWidth, int viewHeight, int positionX, int positionY);
	~Camera();

	void OnUpdate();

	Position GetBottomLeft();

private:
	void DrawSprite(Sprite sprite);
	void DrawCharacter(Character character, Position pos);
	void DrawCharacterForeground(Character character, Position pos);
};

#endif // CAMERA