#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <vector>
#include <string>
#include "Character.h"
#include "Int2D.h"

class Texture {
private:
	std::vector<Character> characters;
	Int2D dimensions;
public:
	Texture();
	Texture(Int2D newDimensions);
	Texture(std::wstring newCharacters, int spriteWidth, TextColor textColor = TextColor::White, BackColor backgroundColor = BackColor::Black);

	int GetWidth() { return dimensions.x; }
	int GetHeight() { return dimensions.y; }
	Int2D GetDimensions() { return dimensions; }
	std::vector<Character> GetCharacters() { return characters; }

	void SetTexture(std::wstring newTexture, int spriteWidth, TextColor textColor = TextColor::White, BackColor backgroundColor = BackColor::Black);
	void SetColor(TextColor textColor = TextColor::White, BackColor backgroundColor = BackColor::Black);

	void ClearCharacters(Character clearChar = Character(' ', TextColor::White, BackColor::Black));
	void DrawCharacter(Character character, Int2D pos);
	void DrawCharacterForeground(Character character, Int2D pos);
};

#endif // TEXTURE_H