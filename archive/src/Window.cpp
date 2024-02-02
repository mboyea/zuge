#include "Window.h"

Window::Window(Int2D windowDimensions, LPCWSTR windowTitle) {
	screenBuffer = Texture(windowDimensions);
	SetTitle(windowTitle);
}

void Window::Update() {

}

LPCWSTR Window::SetTitle(LPCWSTR newTitle) {
	title = newTitle;
	// TODO: implement window title setting logic
	return title;
}
