#ifndef TRANSFORM_H
#define TRANSFORM_H
#pragma once

#include "Component.h"
#include "Int2D.h"

struct Transform : Component {
public:
	Int2D position;
};

#endif // TRANSFORM_H