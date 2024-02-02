#include "InputTracker.h"
#include <cstring>

InputTracker::InputTracker() {
	mousePos = Position(1, 1);
}

InputTracker::~InputTracker() {

}

void InputTracker::OnUpdate() {
    std::memcpy(lastKeys, keys, sizeof(lastKeys));
    GetKeyState(0);
    GetKeyboardState(keys);
}

bool InputTracker::IsKeyPressed(int virtualKey) {
    if (keys[virtualKey] > 1) { // if key is down this frame
        if (!(lastKeys[virtualKey] > 1)) { // if key was up last frame
            return true;
        }
        else return false;
    }
    else return false;
}

bool InputTracker::IsKeyReleased(int virtualKey) {
    if (lastKeys[virtualKey] > 1) { // if key was down last frame
        if (!(keys[virtualKey] > 1)) { // if key is up this frame
            return true;
        }
        else return false;
    }
    else return false;
}

bool InputTracker::IsKeyDown(int virtualKey) {
    return keys[virtualKey] > 1;
}

bool InputTracker::IsKeyUp(int virtualKey) {
    return !(keys[virtualKey] > 1);
}

Position InputTracker::GetMouseToWindow() {
	INPUT_RECORD input[128];
	DWORD eventsRead;
    GetNumberOfConsoleInputEvents(window->consoleInput, &eventsRead);
	if (eventsRead > 0) {
            ReadConsoleInput(
                window->consoleInput,
                input,
                128,
                &eventsRead
            );
            for (unsigned int i = 0; i < eventsRead; i++) {
                switch (input[i].EventType) {
                case MOUSE_EVENT:
                    switch (input[i].Event.MouseEvent.dwEventFlags) {
                    case MOUSE_MOVED:
                        mousePos.x = input[i].Event.MouseEvent.dwMousePosition.X + 1;
                        mousePos.y = window->GetHeight() - input[i].Event.MouseEvent.dwMousePosition.Y;
                        break;
                    default:
                        break;
                    }
                case KEY_EVENT:
                    // Disregard
                case FOCUS_EVENT:
                    // Disregard
                    break;
                case MENU_EVENT:
                    // Disregard
                    break;
                case WINDOW_BUFFER_SIZE_EVENT:
                    // Disregard
                    break;
                }
            }
        }
	return mousePos;
}

Position InputTracker::GetMouseToWorld() {
    return GetMouseToWindow() + window->GetCamera()->GetBottomLeft() - Position(1, 1);
}
