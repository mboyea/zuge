#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include "Component.h"
#include "Texture.h"
#include "Pivot.h"
#include "RenderType.h"

struct Sprite : Component {
public:
	Texture texture;
	Pivot pivot = Pivot::BottomLeft;
	RenderType renderType = RenderType::Opaque;
	bool overwriteBackground = true;

	Int2D GetDimensions() {
		return Int2D(texture.GetWidth(), texture.GetHeight());
	}
};

#endif // SPRITE_H