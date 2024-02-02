#include "Texture.h"

Texture::Texture() {
	dimensions = Int2D(1, 1);

	// Generate default sprite texture.
	Character defaultTexture;
	defaultTexture.textChar = L'☒';
	defaultTexture.textColor = TextColor::White;
	defaultTexture.backColor = BackColor::Black;

	// Push the default sprite texture
	characters.clear();
	characters.push_back(defaultTexture);
}

Texture::Texture(Int2D newDimensions) {
	dimensions = newDimensions;

	// Initialize characters
	while (characters.size() < (unsigned int)dimensions.x * (unsigned int)dimensions.y) {
		Character character;
		character.textChar = L' ';
		character.textColor = TextColor::White;
		character.backColor = BackColor::Black;
		characters.push_back(character);
	}
	characters.reserve(dimensions.x * dimensions.y);
}

Texture::Texture(std::wstring newTexture, int spriteWidth, TextColor textColor, BackColor backgroundColor) {
	dimensions.x = spriteWidth;
	dimensions.y = (newTexture.size() / spriteWidth);

	characters.clear();
	for (int i = 0; i < dimensions.x * dimensions.y; i++) {
		Character character;
		character.textChar = newTexture[i];
		character.textColor = textColor;
		character.backColor = backgroundColor;
		characters.push_back(character);
	}
}

void Texture::SetTexture(std::wstring newTexture, int spriteWidth, TextColor textColor, BackColor backgroundColor) {
	dimensions.x = spriteWidth;
	dimensions.y = (newTexture.size() / spriteWidth);

	characters.clear();
	for (int i = 0; i < dimensions.x * dimensions.y; i++) {
		Character character;
		character.textChar = newTexture[i];
		character.textColor = textColor;
		character.backColor = backgroundColor;
		characters.push_back(character);
	}
}

void Texture::SetColor(TextColor textColor, BackColor backgroundColor) {
	for (int i = 0; i < dimensions.x * dimensions.y; i++) {
		Character* character = &characters[i];
		character->textColor = textColor;
		character->backColor = backgroundColor;
	}
}

void Texture::ClearCharacters(Character clearChar) {
	// Clear the screen buffer
	for (int y = 0; y < dimensions.y; y++) {
		for (int x = 0; x < dimensions.x; x++) {
			characters[x + dimensions.x * y] = clearChar;
		}
	}
}

void Texture::DrawCharacter(Character character, Int2D pos) {
	// if inside screen bounds
	if (pos.x > 0 && pos.x <= dimensions.x && pos.y > 0 && pos.y < dimensions.y + 1) {
		// draw to screen
		characters[pos.x - 1 + dimensions.x * (dimensions.y - pos.y)] = character;
	}
}

void Texture::DrawCharacterForeground(Character character, Int2D pos) {
	// if inside screen bounds
	if (pos.x > 0 && pos.x <= dimensions.x && pos.y > 0 && pos.y < dimensions.y + 1) {
		Character* targetCharacter = &characters[pos.x - 1 + dimensions.x * (dimensions.y - pos.y)];
		character.backColor = targetCharacter->backColor;
		// draw to screen
		*targetCharacter = character;
	}
}
