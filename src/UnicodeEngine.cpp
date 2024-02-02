#include "UnicodeEngine.h"

UnicodeEngine::UnicodeEngine(Scene* scene, Window* window) {
	activeScene = scene;
	activeWindow = window;
	input = InputTracker();
	input.window = window;
}

UnicodeEngine::~UnicodeEngine() {

}

void UnicodeEngine::Update() {
	activeScene->OnUpdate();
	activeWindow->OnUpdate();
	input.OnUpdate();
	time.OnUpdate();
}