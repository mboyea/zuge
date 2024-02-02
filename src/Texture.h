#ifndef TEXTURE
#define TEXTURE
#pragma once

#include "Character.h"
#include <Windows.h>
#include <vector>
#include <string>

class Texture {
private:
	int width = 1, height = 1;
	std::vector<Character> characters;
public:
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	std::vector<Character>& GetCharacters() { return characters; }

	Texture();
	Texture(std::wstring newTexture, int spriteWidth, TextColor textColor, BackColor backgroundColor = BackColor::Black);
	Texture(std::wstring newTexture, int spriteWidth, TextColor textColor[], BackColor backgroundColor[]);

	void SetTexture(std::string filePath);
	void SetTexture(std::wstring newTexture, int spriteWidth, TextColor textColor, BackColor backgroundColor);
	void SetTexture(std::wstring newTexture, int spriteWidth, TextColor textColor[], BackColor backgroundColor[]);
	void SetColor(TextColor textColor, BackColor backgroundColor);
};

#endif // TEXTURE