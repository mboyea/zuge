#include "UnicodeEngine.h"

int main() {
	UnicodeEngine UGE(Int2D(120, 30));
	Scene* scene = &UGE.activeScene;
	Window* window = &UGE.activeWindow;

	window->SetTitle(L"Window Title!");
	EntityID player = scene->NewEntity("Player");
	Sprite* playerSprite = scene->AddComponent<Sprite>(player);
	Transform* playerTransform = scene->GetComponent<Transform>(player);

	std::wstring playerText;
	playerText += L"(⌁⎽￩)､   ";
	playerText += L"︻┳ア═╦━━─-";
	playerText += L" ⤤ ⤤     ";
	playerSprite->texture = Texture(playerText, 9);

	while (true) {
		UGE.Update();
	}

	return 0;
}