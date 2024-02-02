#ifndef COMPONENTS_H
#define COMPONENTS_H
#pragma once

#include <bitset>

#include "Name.h"
#include "Transform.h"
#include "Sprite.h"
#include "Camera.h"

enum CompTypeID {
	IDName,
	IDTransform,
	IDSprite,
	IDCamera,
	TOTAL_COMPONENT_TYPES,
	IDNotAComponent
};

template<typename T> CompTypeID TypeToID() {
	if (std::is_same<T, Name>()) {
		return IDName;
	}
	else if (std::is_same<T, Transform>()) {
		return IDTransform;
	}
	else if (std::is_same<T, Sprite>()) {
		return IDSprite;
	}
	else if (std::is_same<T, Camera>()) {
		return IDCamera;
	}
	else return IDNotAComponent;
}

// Component Signature
typedef std::bitset<TOTAL_COMPONENT_TYPES> Signature;

inline Signature IDToSignature(CompTypeID ID) {
	Signature signature;
	if (ID < TOTAL_COMPONENT_TYPES) {
		signature.set(ID);
	}
	return signature;
}

// Generate a component signature, up to 16 components wide
inline Signature GenerateSignature(
	CompTypeID component01 = IDNotAComponent, CompTypeID component02 = IDNotAComponent,
	CompTypeID component03 = IDNotAComponent, CompTypeID component04 = IDNotAComponent,
	CompTypeID component05 = IDNotAComponent, CompTypeID component06 = IDNotAComponent,
	CompTypeID component07 = IDNotAComponent, CompTypeID component08 = IDNotAComponent,
	CompTypeID component09 = IDNotAComponent, CompTypeID component10 = IDNotAComponent,
	CompTypeID component11 = IDNotAComponent, CompTypeID component12 = IDNotAComponent,
	CompTypeID component13 = IDNotAComponent, CompTypeID component14 = IDNotAComponent,
	CompTypeID component15 = IDNotAComponent, CompTypeID component16 = IDNotAComponent
) {
	Signature signature;
	signature = IDToSignature(component01) | IDToSignature(component02) |
		IDToSignature(component03) | IDToSignature(component04) |
		IDToSignature(component05) | IDToSignature(component06) |
		IDToSignature(component07) | IDToSignature(component08) |
		IDToSignature(component09) | IDToSignature(component10) |
		IDToSignature(component11) | IDToSignature(component12) |
		IDToSignature(component13) | IDToSignature(component14) |
		IDToSignature(component15) | IDToSignature(component16);
	return signature;
}

// Component Index
typedef int CompIndex;

const CompIndex NO_COMPONENT = -1;

#endif // COMPONENTS_H