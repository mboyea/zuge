#ifndef SPRITE
#define SPRITE
#pragma once

#include "Position.h"
#include "Texture.h"
#include "Pivot.h"
#include "RenderType.h"
#include "Script.h"
#include <Windows.h>
#include <vector>
#include <string>

class Sprite {
public:
	std::wstring name = L"";
	Position position = Position(1, 1);
	Texture texture = Texture();
	Pivot pivot = Pivot::BottomLeft;
	RenderType renderType = Opaque;
	bool overwriteBackground = true;

	std::vector<Script*> scripts;

	Sprite(std::wstring newName);
	Sprite(std::wstring newName, Texture newTexture);
	~Sprite();

	void OnStart();
	void OnUpdate();

	// template<typename T> Script* AddScript();
	Script* AddScript(Script* script);
	Position GetBottomLeft();
};

#endif // SPRITE