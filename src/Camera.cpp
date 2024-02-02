#include "Camera.h"
#include <cmath>

Camera::Camera(int viewWidth, int viewHeight) {
	width = viewWidth;
	height = viewHeight;

	// Initialize buffer
	while (screenBuffer.size() < (unsigned int)width * (unsigned int)height) {
		Character character;
		character.textChar = ' ';
		character.textColor = TextColor::White;
		character.backColor = BackColor::Black;
		screenBuffer.push_back(character);
	}
	screenBuffer.reserve(width * height);
}

Camera::Camera(int viewWidth, int viewHeight, int positionX, int positionY) {
	width = viewWidth;
	height = viewHeight;
	position = Position(positionX, positionY);

	// Initialize buffer
	while (screenBuffer.size() < (unsigned int)width * (unsigned int)height) {
		Character character;
		character.textChar = ' ';
		character.textColor = TextColor::White;
		character.backColor = BackColor::Black;
		screenBuffer.push_back(character);
	}
	screenBuffer.reserve(width * height);
}

Camera::~Camera() {

}

void Camera::OnUpdate() {
	// Clear the screen buffer
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			screenBuffer[x + width * y].textChar = ' ';
			screenBuffer[x + width * y].textColor = TextColor::White;
			screenBuffer[x + width * y].backColor = BackColor::Black;
		}
	}

	// for each sprite in the render list
	for (Sprite sprite : *renderList) {
		DrawSprite(sprite);
	}
}

Position Camera::GetBottomLeft() {
	Position bottomLeft(1, 1);
	switch (pivot) {
	case Pivot::BottomLeft:
		bottomLeft = position;
		break;
	case Pivot::BottomRight:
		bottomLeft = position;
		bottomLeft.x -= (width - 1);
		break;
	case Pivot::TopLeft:
		bottomLeft = position;
		bottomLeft.y -= (height - 1);
		break;
	case Pivot::TopRight:
		bottomLeft = position;
		bottomLeft.x -= (width - 1);
		bottomLeft.y -= (height - 1);
		break;
	case Pivot::Center:
		bottomLeft = position;
		bottomLeft.x -= (int)ceil(width / 2);
		bottomLeft.y -= (int)ceil(height / 2);
		break;
	}
	return bottomLeft;
}

void Camera::DrawSprite(Sprite sprite) {
	const std::vector<Character> spriteCharacters = sprite.texture.GetCharacters();
	const int spriteWidth = sprite.texture.GetWidth();
	const int spriteHeight = sprite.texture.GetHeight();

	// spritePos - cameraPos + 1
	Position bottomLeft = sprite.GetBottomLeft() - GetBottomLeft() + Position(1, 1);

	if (sprite.overwriteBackground) {
		switch (sprite.renderType) {
		case RenderType::Opaque:
			// for each character in the texture, find it's position on the window and draw it to the buffer
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				Position pos;
				//	Formula: Row# = ceil(Element# / Width)
				//	posX = BottomLeftX + Element# - Width * Row#
				//	posY = BottomLeftY + Height - 1 - Row#
				pos.x = bottomLeft.x + i - spriteWidth * (int)ceil(i / spriteWidth);
				pos.y = bottomLeft.y + spriteHeight - 1 - (int)ceil(i / spriteWidth);

				DrawCharacter(spriteCharacters[i], pos);
			}
			break;
		case RenderType::Filled:
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				Position pos;
				pos.x = bottomLeft.x + i - spriteWidth * (int)ceil(i / spriteWidth);
				pos.y = bottomLeft.y + spriteHeight - 1 - (int)ceil(i / spriteWidth);

				// '%' is transparent
				if (spriteCharacters[i].textChar != '%') {
					DrawCharacter(spriteCharacters[i], pos);
				}
			}
			break;
		case RenderType::Transparent:
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				Position pos;
				pos.x = bottomLeft.x + i - spriteWidth * (int)ceil(i / spriteWidth);
				pos.y = bottomLeft.y + spriteHeight - 1 - (int)ceil(i / spriteWidth);

				// ' ' is transparent
				if (spriteCharacters[i].textChar != ' ') {
					DrawCharacter(spriteCharacters[i], pos);
				}
			}
			break;
		}
	}
	else {
		switch (sprite.renderType) {
		case RenderType::Opaque:
			// for each character in the texture, find it's position on the window and draw it to the buffer
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				Position pos;
				//	Formula: Row# = ceil(Element# / Width)
				//	posX = BottomLeftX + Element# - Width * Row#
				//	posY = BottomLeftY + Height - 1 - Row#
				pos.x = bottomLeft.x + i - spriteWidth * (int)ceil(i / spriteWidth);
				pos.y = bottomLeft.y + spriteHeight - 1 - (int)ceil(i / spriteWidth);

				DrawCharacterForeground(spriteCharacters[i], pos);
			}
			break;
		case RenderType::Filled:
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				Position pos;
				pos.x = bottomLeft.x + i - spriteWidth * (int)ceil(i / spriteWidth);
				pos.y = bottomLeft.y + spriteHeight - 1 - (int)ceil(i / spriteWidth);

				// '%' is transparent
				if (spriteCharacters[i].textChar != '%') {
					DrawCharacterForeground(spriteCharacters[i], pos);
				}
			}
			break;
		case RenderType::Transparent:
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				Position pos;
				pos.x = bottomLeft.x + i - spriteWidth * (int)ceil(i / spriteWidth);
				pos.y = bottomLeft.y + spriteHeight - 1 - (int)ceil(i / spriteWidth);

				// ' ' is transparent
				if (spriteCharacters[i].textChar != ' ') {
					DrawCharacterForeground(spriteCharacters[i], pos);
				}
			}
			break;
		}
	}
}

void Camera::DrawCharacter(Character character, Position pos) {
	// if inside window bounds
	if (pos.x > 0 && pos.x <= width && pos.y > 0 && pos.y < height + 1) {
		// draw to window
		screenBuffer[pos.x - 1 + width * (height - pos.y)] = character;
	}
}

void Camera::DrawCharacterForeground(Character character, Position pos) {
	// if inside window bounds
	if (pos.x > 0 && pos.x <= width && pos.y > 0 && pos.y < height + 1) {
		Character* drawCharacter = &screenBuffer[pos.x - 1 + width * (height - pos.y)];
		character.backColor = drawCharacter->backColor;
		// draw to window
		*drawCharacter = character;
	}
}
