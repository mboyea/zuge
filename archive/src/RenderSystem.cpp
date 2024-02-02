#include "RenderSystem.h"

Int2D GetCharacterDrawPos(Int2D bottomLeft, Int2D spriteDimensions, unsigned int i) {
	Int2D pos;
	//	Formula: Row# = ceil(Element# / Width)
	//	posX = BottomLeftX + Element# - Width * Row#
	//	posY = BottomLeftY + Height - 1 - Row#
	pos.x = bottomLeft.x + i - spriteDimensions.x * (int)ceil(i / spriteDimensions.x);
	pos.y = bottomLeft.y + spriteDimensions.y - 1 - (int)ceil(i / spriteDimensions.x);
	return pos;
}

void RenderSystem::RenderToCamera(Sprite* sprite, Transform* spriteTransform, Camera* camera, Transform* cameraTransform) {
	const std::vector<Character> spriteCharacters = sprite->texture.GetCharacters();

	// spritePos - cameraPos + (1, 1)
	const Int2D bottomLeft =
		GetBottomLeft(sprite->pivot, spriteTransform->position, sprite->GetDimensions())
		- GetBottomLeft(camera->pivot, cameraTransform->position, camera->screenBuffer.GetDimensions())
		+ Int2D(1, 1);
	//TODO: figure out a better way to store GetBottomLeft() functionality

	switch (sprite->renderType) {
	case RenderType::Opaque:
		if (sprite->overwriteBackground) {
			// for each character in the texture, find it's position on the window and draw it to the buffer texture
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				camera->screenBuffer.DrawCharacter(spriteCharacters[i], GetCharacterDrawPos(bottomLeft, sprite->texture.GetDimensions(), i));
			}
		}
		else {
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				camera->screenBuffer.DrawCharacterForeground(spriteCharacters[i], GetCharacterDrawPos(bottomLeft, sprite->texture.GetDimensions(), i));
			}
		}
		break;
	case RenderType::Filled:
		if (sprite->overwriteBackground) {
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				// '%' is transparent
				if (spriteCharacters[i].textChar != '%') {
					camera->screenBuffer.DrawCharacter(spriteCharacters[i], GetCharacterDrawPos(bottomLeft, sprite->texture.GetDimensions(), i));
				}
			}
		}
		else {
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				if (spriteCharacters[i].textChar != '%') {
					camera->screenBuffer.DrawCharacterForeground(spriteCharacters[i], GetCharacterDrawPos(bottomLeft, sprite->texture.GetDimensions(), i));
				}
			}
		}
		break;
	case RenderType::Transparent:
		if (sprite->overwriteBackground) {
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				// ' ' is transparent
				if (spriteCharacters[i].textChar != ' ') {
					camera->screenBuffer.DrawCharacter(spriteCharacters[i], GetCharacterDrawPos(bottomLeft, sprite->texture.GetDimensions(), i));
				}
			}
		}
		else {
			for (unsigned int i = 0; i < spriteCharacters.size(); i++) {
				if (spriteCharacters[i].textChar != ' ') {
					camera->screenBuffer.DrawCharacterForeground(spriteCharacters[i], GetCharacterDrawPos(bottomLeft, sprite->texture.GetDimensions(), i));
				}
			}
		}
		break;
	}
}