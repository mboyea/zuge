#ifndef UISPRITE_H
#define UISPRITE_H
#pragma once

#include "Component.h"
#include "Texture.h"
#include "Pivot.h"
#include "RenderType.h"

struct UISprite : Component {
public:
	Texture texture;
	Pivot pivot = Pivot::BottomLeft;
	RenderType renderType = RenderType::Opaque;
	bool overwriteBackground = true;
};

#endif // UISPRITE_H