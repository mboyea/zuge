#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#pragma once

#include "Components.h"
#include <iostream>

namespace RenderSystem {
	const Signature cameraRequired = GenerateSignature(IDTransform, IDCamera);
	const Signature spriteRequired = GenerateSignature(IDTransform, IDSprite);
	// Render a sprite to a camera
	void RenderToCamera(Sprite* sprite, Transform* spriteTransform, Camera* camera, Transform* cameraTransform);
}

#endif // RENDERSYSTEM_H