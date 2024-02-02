#include "Sprite.h"
#include <cmath>

Sprite::Sprite(std::wstring newName) {
	name = newName;
	texture = Texture();
	position = Position(1, 1);
}

Sprite::Sprite(std::wstring newName, Texture newTexture) {
	name = newName;
	texture = newTexture;
	position = Position(1, 1);
}

Sprite::~Sprite() {

}

void Sprite::OnStart() {
	for (auto& script : scripts) {
		script->OnStart();
	}
}

void Sprite::OnUpdate() {
	for (auto& script : scripts) {
		script->OnUpdate();
	}
}

/*template<typename T> Script* Sprite::AddScript<Script*>() {
	T script;
	script->sprite = this;
	scripts.push_back(script);
	scripts.back()->OnStart();
	return scripts.back();
}*/

Script* Sprite::AddScript(Script* script) {
	script->sprite = this;
	scripts.push_back(script);
	scripts.back()->OnStart();
	return scripts.back();
}

Position Sprite::GetBottomLeft() {
	Position bottomLeft(1, 1);
	switch (pivot) {
	case Pivot::BottomLeft:
		bottomLeft = position;
		break;
	case Pivot::BottomRight:
		bottomLeft = position;
		bottomLeft.x -= (texture.GetWidth() - 1);
		break;
	case Pivot::TopLeft:
		bottomLeft = position;
		bottomLeft.y -= (texture.GetHeight() - 1);
		break;
	case Pivot::TopRight:
		bottomLeft = position;
		bottomLeft.x -= (texture.GetWidth() - 1);
		bottomLeft.y -= (texture.GetHeight() - 1);
		break;
	case Pivot::Center:
		bottomLeft = position;
		bottomLeft.x -= (int)ceil(texture.GetWidth() / 2);
		bottomLeft.y -= (int)ceil(texture.GetHeight() / 2);
		break;
	}
	return bottomLeft;
}
