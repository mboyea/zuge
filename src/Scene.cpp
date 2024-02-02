#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::OnUpdate() {
	for (auto& camera : cameras) {
		camera.OnUpdate();
	}
	for (auto& sprite : sprites) {
		sprite.OnStart();
	}
}

Camera* Scene::NewCamera(int viewWidth, int viewHeight) {
	Camera camera(viewWidth, viewHeight);
	camera.renderList = &sprites;
	cameras.push_back(camera);
	return &cameras.back();
}

Camera* Scene::NewCamera(int viewWidth, int viewHeight, int positionX, int positionY) {
	Camera camera(viewWidth, viewHeight, positionX, positionY);
	camera.renderList = &sprites;
	cameras.push_back(camera);
	return &cameras.back();
}

Camera* Scene::GetCamera(unsigned int elementID) {
	return &cameras.at(elementID);
}
/*
Camera* Scene::GetCamera(std::string cameraName) {
	
}*/

Sprite* Scene::NewSprite(std::wstring spriteName) {
	Sprite sprite(spriteName);
	sprites.push_back(sprite);
	return &sprites.back();
}

Sprite* Scene::NewSprite(std::wstring spriteName, Texture spriteTexture) {
	Sprite sprite(spriteName, spriteTexture);
	sprites.push_back(sprite);
	return &sprites.back();
}

Sprite* Scene::GetSprite(unsigned int elementID) {
	return &sprites.at(elementID);
}

Sprite* Scene::GetSprite(std::wstring entityName) {
	for (size_t i = 0; i < sprites.size(); i++) {
		if (sprites[i].name == entityName) {
			return &sprites[i];
		}
	}
	// otherwise there is no entity with that name
	return nullptr;
}