#ifndef SCENE
#define SCENE
#pragma once

#include "Camera.h"
#include "Sprite.h"
#include <vector>
#include <string>

class Scene {
public:
	std::vector<Camera> cameras;
	std::vector<Sprite> sprites;

	Scene();
	~Scene();

	void OnUpdate();
	Camera* NewCamera(int viewWidth, int viewHeight);
	Camera* NewCamera(int viewWidth, int viewHeight, int positionX, int positionY);
	Camera* GetCamera(unsigned int elementID);
	// TODO: Camera* GetCameraID(std::string cameraName);
	Sprite* NewSprite(std::wstring spriteName);
	Sprite* NewSprite(std::wstring spriteName, Texture spriteTexture);
	Sprite* GetSprite(unsigned int elementID);
	Sprite* GetSprite(std::wstring spriteName);
};

#endif // SCENE