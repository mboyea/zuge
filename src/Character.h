#ifndef CHARACTER
#define CHARACTER
#pragma once

#include "TextColor.h"
#include "BackColor.h"

struct Character {
	WCHAR textChar;
	TextColor textColor;
	BackColor backColor;
};

#endif // CHARACTER