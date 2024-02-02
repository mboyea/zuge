#ifndef CHARACTER_H
#define CHARACTER_H
#pragma once

#define NOMINMAX
#include <Windows.h>
#include "TextColor.h"
#include "BackColor.h"

struct Character {
	WCHAR textChar;
	TextColor textColor;
	BackColor backColor;

	Character(WCHAR newTextChar = ' ', TextColor newTextColor = TextColor::White, BackColor newBackColor = BackColor::Black) {
		textChar = newTextChar;
		textColor = newTextColor;
		backColor = newBackColor;
	}
};

#endif // CHARACTER_H