#include "UnicodeEngine.h"

UnicodeEngine::UnicodeEngine() {
	activeScene = Scene();
	activeWindow = Window();
}

UnicodeEngine::UnicodeEngine(Int2D windowDimensions) {
	activeScene = Scene();
	activeWindow = Window(windowDimensions);
}

UnicodeEngine::UnicodeEngine(Int2D windowDimensions, LPCWSTR windowName) {
	activeScene = Scene();
	activeWindow = Window(windowDimensions, windowName);
}

void UnicodeEngine::Update() {
	activeScene.Update();
	activeWindow.Update();
}