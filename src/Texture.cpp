#include "Texture.h"

Texture::Texture() {
	width = 1;
	height = 1;

	// Generate default sprite texture.
	Character defaultTexture;
	defaultTexture.textChar = L'☒';
	defaultTexture.textColor = TextColor::White;
	defaultTexture.backColor = BackColor::Black;

	// Push the default sprite texture
	characters.clear();
	characters.push_back(defaultTexture);
}

Texture::Texture(std::wstring newTexture, int spriteWidth, TextColor textColor, BackColor backgroundColor) {
	width = spriteWidth;
	height = (newTexture.size() / spriteWidth);

	characters.clear();
	for (int i = 0; i < width * height; i++) {
		Character character;
		character.textChar = newTexture[i];
		character.textColor = textColor;
		character.backColor = backgroundColor;
		characters.push_back(character);
	}
}

Texture::Texture(std::wstring newTexture, int spriteWidth, TextColor textColor[], BackColor backgroundColor[]) {
	width = spriteWidth;
	height = (newTexture.size() / spriteWidth);

	characters.clear();
	for (int i = 0; i < width * height; i++) {
		Character character;
		character.textChar = newTexture[i];
		character.textColor = textColor[i];
		character.backColor = backgroundColor[i];
		characters.push_back(character);
	}
}

void Texture::SetTexture(std::string filePath) {
	// TODO: texture from filepath support
}

void Texture::SetTexture(std::wstring newTexture, int spriteWidth, TextColor textColor, BackColor backgroundColor) {
	width = spriteWidth;
	height = (newTexture.size() / spriteWidth);

	characters.clear();
	for (int i = 0; i < width * height; i++) {
		Character character;
		character.textChar = newTexture[i];
		character.textColor = textColor;
		character.backColor = backgroundColor;
		characters.push_back(character);
	}
}

void Texture::SetTexture(std::wstring newTexture, int spriteWidth, TextColor textColor[], BackColor backgroundColor[]) {
	width = spriteWidth;
	height = (newTexture.size() / spriteWidth);

	characters.clear();
	for (int i = 0; i < width * height; i++) {
		Character character;
		character.textChar = newTexture[i];
		character.textColor = textColor[i];
		character.backColor = backgroundColor[i];
		characters.push_back(character);
	}
}

void Texture::SetColor(TextColor textColor, BackColor backgroundColor) {
	for (int i = 0; i < width * height; i++) {
		Character* character = &characters[i];
		character->textColor = textColor;
		character->backColor = backgroundColor;
	}
}
