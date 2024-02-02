#include "Window.h"
#include <cmath>

Window::Window(int winWidth, int winHeight, LPCWSTR winTitle) {
	width = winWidth;
	height = winHeight;
	title = winTitle;

	screenBufferPosition = { 0, 0 };
	screenBufferSize = { (SHORT)width, (SHORT)height };
	windowSize = { 0, 0, (SHORT)width - 1, (SHORT)height - 1 };

	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleInput = GetStdHandle(STD_INPUT_HANDLE);
	consoleWindow = GetConsoleWindow();

	// Set Window Title
	SetTitle(title);
	// Set Window Size
	SetConsoleWindowInfo(consoleOutput, TRUE, &windowSize);
	// Enable Mouse Input
	SetConsoleMode(consoleInput, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
	// Set Window Style (not resizeable)
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	// Set Screen Buffer Size
	SetConsoleScreenBufferSize(consoleOutput, screenBufferSize);
}
Window::~Window() {

}

void Window::OnUpdate() {
	// Update window buffer from camera
	if (activeCamera != nullptr) {
		screenBuffer = activeCamera->screenBuffer;
	}

	// Draw window sprites
	for (Sprite sprite : sprites) {
		DrawSprite(sprite);
	}

	// Initialize CHAR_INFO buffer
	std::vector<CHAR_INFO> charBuffer;
	while (charBuffer.size() < (unsigned int)width * (unsigned int)height) {
		CHAR_INFO character;
		character.Char.UnicodeChar = ' ';
		character.Attributes = 15;
		charBuffer.push_back(character);
	}
	screenBuffer.reserve(width * height);

	// Convert Character to CHAR_INFO
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int arrayElement = x + width * y;
			charBuffer[arrayElement].Char.UnicodeChar = screenBuffer[arrayElement].textChar;
			charBuffer[arrayElement].Attributes =
				(WORD)screenBuffer[arrayElement].textColor |
				(WORD)screenBuffer[arrayElement].backColor;
		}
	}
	// Write the screen buffer
	WriteConsoleOutput(consoleOutput, charBuffer.data(), screenBufferSize, screenBufferPosition, &windowSize);
}

Camera* Window::SetCamera(Camera* camera) {
	activeCamera = camera;
	return activeCamera;
}

void Window::SetTitle(LPCWSTR winTitle) {
	title = winTitle;
	SetConsoleTitle(title);
}

/*bool Window::ShowMouseCursor(bool doShowCursor) {
	// SetCursor(LoadCursor((HINSTANCE)consoleWindow, IDC_HAND));
	// SetCursor(LoadCursor((HINSTANCE)GetWindowLong(consoleWindow, GWL_HINSTANCE), IDC_HAND));
	// SetCursor(LoadCursor(GetModuleHandle(NULL), IDC_HAND));
	// SetCursor(NULL);
	//TODO: figure out how to disable the mouse cursor
	return doShowCursor;
}*/

void Window::DrawSprite(Sprite sprite) {
	const std::vector<Character> spriteCharacters = sprite.texture.GetCharacters();
	const int spriteWidth = sprite.texture.GetWidth();
	const int spriteHeight = sprite.texture.GetHeight();

	Position bottomLeft = sprite.GetBottomLeft();

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

void Window::DrawCharacter(Character character, Position pos) {
	// if inside window bounds
	if (pos.x > 0 && pos.x <= width && pos.y > 0 && pos.y < height + 1) {
		// draw to window
		screenBuffer[pos.x - 1 + width * (height - pos.y)] = character;
	}
}

void Window::DrawCharacterForeground(Character character, Position pos) {
	// if inside window bounds
	if (pos.x > 0 && pos.x <= width && pos.y > 0 && pos.y < height + 1) {
		Character* drawCharacter = &screenBuffer[pos.x - 1 + width * (height - pos.y)];
		character.backColor = drawCharacter->backColor;
		// draw to window
		*drawCharacter = character;
	}
}

Sprite* Window::NewSprite(std::wstring spriteName) {
	Sprite sprite(spriteName);
	sprites.push_back(sprite);
	return &sprites.back();
}

Sprite* Window::NewSprite(std::wstring spriteName, Texture spriteTexture) {
	Sprite sprite(spriteName, spriteTexture);
	sprites.push_back(sprite);
	return &sprites.back();
}

Sprite* Window::GetSprite(unsigned int elementID) {
	return &sprites.at(elementID);
}

Sprite* Window::GetSprite(std::wstring entityName) {
	for (size_t i = 0; i < sprites.size(); i++) {
		if (sprites[i].name == entityName) {
			return &sprites[i];
		}
	}
	// otherwise there is no entity with that name
	return nullptr;
}
