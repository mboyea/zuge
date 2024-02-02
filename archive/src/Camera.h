#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "Component.h"
#include "Pivot.h"
#include "Texture.h"

struct Camera : Component {
public:
	Texture screenBuffer;
	Pivot pivot = Pivot::BottomLeft;
};

#endif // CAMERA_H