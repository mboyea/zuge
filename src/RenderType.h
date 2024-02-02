#ifndef RENDERTYPE
#define RENDERTYPE
#pragma once

enum RenderType {
	Opaque = 0,	// ' ' overwrites text.
	Filled,		// ' ' overwrites text. '%' is ignored (transparent).
	Transparent // ' ' is ignored (transparent).
};

#endif // RENDERTYPE