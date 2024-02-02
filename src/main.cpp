#include "UnicodeEngine.h"

int main() {
	// Create a new scene
	Scene scene;
	// Create a new window
	Window window(120, 30, L"Game Window");
	// Create a new camera in the scene
	Camera* camera = scene.NewCamera(120, 30, 1, 1);
	camera->pivot = Pivot::BottomLeft;
	// Set the window cam to the camera
	window.SetCamera(camera);

	// Create a new texture
	std::wstring testText;
	testText += L"Text looks like";
	testText += L"this txt sample";
	testText += L"               ";
	testText += L"︻╦╤─⎺⎻⎻⎼⎼⎽⎽    ";
	testText += L"           ⎺⎺⎻⎻";
	testText += L"   ┌┳⎺╦─⎺      ";
	testText += L"   ︻╦テ╤━-      ";
	testText += L"   ︻╤デ═一⎻      ";
	testText += L"   ︻┳ア═╦━━─-   ";

	std::wstring charText;
	charText += L"(⌁⎽￩)､   ";
	charText += L"︻┳ア═╦━━─-";
	charText += L" ⤤ ⤤     ";

	Texture testTexture(charText, 9, TextColor::White, BackColor::Blue);

	// Create a new sprite in the scene
	Sprite* testSprite = window.NewSprite(L"name", testTexture);
	testSprite->position = Position(1, 1);
	testSprite->pivot = Pivot::BottomLeft;
	testSprite->renderType = RenderType::Transparent;
	testSprite->overwriteBackground = false;

	Texture cursorTexture((std::wstring)L"/ \\ o \\ /", 3, TextColor::Red, BackColor::Black);
	Sprite* cursorSprite = window.NewSprite(L"cursor", cursorTexture);
	cursorSprite->pivot = Pivot::Center;
	cursorSprite->renderType = RenderType::Transparent;
	cursorSprite->overwriteBackground = false;

	//update pointer after reallocation //TODO:
	testSprite = window.GetSprite(L"name");
	// Create an instance of the game
	UnicodeEngine UGE(&scene, &window);
	int state = 0;
	while (true) {
		// Move cursor to mouse position
		cursorSprite->position = UGE.input.GetMouseToWorld();

		// Control testSprite location
		if (UGE.input.IsKeyPressed('W')) {
			testSprite->position.y += 1;
		}
		if (UGE.input.IsKeyPressed('S')) {
			testSprite->position.y -= 1;
		}
		if (UGE.input.IsKeyPressed('A')) {
			testSprite->position.x -= 1;
		}
		if (UGE.input.IsKeyPressed('D')) {
			testSprite->position.x += 1;
		}
		if (UGE.input.IsKeyDown(VK_UP)) {
			testSprite->position.y += 1;
		}
		if (UGE.input.IsKeyDown(VK_DOWN)) {
			testSprite->position.y -= 1;
		}
		if (UGE.input.IsKeyDown(VK_LEFT)) {
			testSprite->position.x -= 1;
		}
		if (UGE.input.IsKeyDown(VK_RIGHT)) {
			testSprite->position.x += 1;
		}
		// Update the game
		UGE.Update();
	}
	return 0;
}