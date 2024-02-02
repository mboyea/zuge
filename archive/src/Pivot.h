#ifndef PIVOT_H
#define PIVOT_H
#pragma once

#include "Int2D.h"
#include <math.h>

enum Pivot {
	BottomLeft = 0,
	BottomRight,
	TopLeft,
	TopRight,
	Center
};

inline Int2D GetBottomLeft(Pivot pivot, Int2D position, Int2D dimensions) {
	Int2D bottomLeft = position;
	switch (pivot) {
	case Pivot::BottomLeft:
		break;
	case Pivot::BottomRight:
		bottomLeft.x -= (dimensions.x - 1);
		break;
	case Pivot::TopLeft:
		bottomLeft.y -= (dimensions.y - 1);
		break;
	case Pivot::TopRight:
		bottomLeft.x -= (dimensions.x - 1);
		bottomLeft.y -= (dimensions.y - 1);
		break;
	case Pivot::Center:
		bottomLeft.x -= (int)ceil(dimensions.x / 2);
		bottomLeft.y -= (int)ceil(dimensions.y / 2);
		break;
	}
	return bottomLeft;
}


#endif // PIVOT_H