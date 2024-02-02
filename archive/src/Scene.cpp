#include "Scene.h"

Scene::Scene() {

}

void Scene::Update() {
	// RENDER SYSTEM
	for (EntityID cameraEntityID : GetEntitiesWithComponents(RenderSystem::cameraRequired)) {
		for (EntityID spriteEntityID : GetEntitiesWithComponents(RenderSystem::spriteRequired)) {
			RenderSystem::RenderToCamera(
				GetComponent<Sprite>(spriteEntityID),
				GetComponent<Transform>(spriteEntityID),
				GetComponent<Camera>(cameraEntityID),
				GetComponent<Transform>(cameraEntityID)
			);

		}
	}
}

EntityID Scene::GetEntityIDCount() {
	return (EntityID)componentIndexes[0].size();
}

EntityID Scene::GenerateNewEntityID() {
	EntityID newID;
	if (oldEntityIDs.empty()) {
		newID =	(EntityID)componentIndexes[0].size();
	}
	else {
		newID = oldEntityIDs.front();
		oldEntityIDs.pop();
	}
	return newID;
}

CompIndex Scene::GenerateNewCompIndex(CompTypeID typeID) {
	CompIndex newIndex;
	if (oldCompIndexes[typeID].empty()) {
		newIndex = components[typeID].size();
	}
	else {
		newIndex = oldCompIndexes[typeID].front();
		oldCompIndexes[typeID].pop();
	}
	return newIndex;
}

EntityID Scene::NewEntity() {
	// generate entity ID
	EntityID entityID = GenerateNewEntityID();
	// populate entity index
	for (CompTypeID i = (CompTypeID)0; i < TOTAL_COMPONENT_TYPES; i = (CompTypeID)((int)i + 1)) {
		if (entityID + 1 > (EntityID)componentIndexes[i].size()) {
			componentIndexes[i].resize(entityID + 1, NO_COMPONENT);
		}
		componentIndexes[i][entityID] = NO_COMPONENT;
	}
	// add default entity components
	AddComponent<Name>(entityID)->name = "Entity" + std::to_string(entityID);
	AddComponent<Transform>(entityID);
	return entityID;
}

EntityID Scene::NewEntity(std::string entityName) {
	GetComponent<Name>(NewEntity())->name = entityName;
	return EntityID();
}

EntityID Scene::GetEntityID(std::string entityName) {
	for (EntityID entityID : GetEntitiesWithComponents(IDName)) {
		if (GetComponent<Name>(entityID)->name == entityName) {
			return entityID;
		}
	}
	return NO_ENTITY;
}

Signature Scene::GetEntityComponentSignature(EntityID entityID) {
	Signature signature;
	// for each component type
	for (CompTypeID i = (CompTypeID)0; i < TOTAL_COMPONENT_TYPES; i = (CompTypeID)((int)i + 1)) {
		// if component type is on entity
		if (componentIndexes[i][entityID] != NO_COMPONENT) {
			// mark that bit of the signature to true
			signature.set(i);
		}
	}
	return signature;
}

std::vector<EntityID> Scene::GetEntitiesWithComponents(Signature requiredComponents) {
	std::vector<EntityID> entities;
	// for each entity
	for (EntityID e = 0; e < GetEntityIDCount(); e++) {
		Signature entityComponents = GetEntityComponentSignature(e);
		// for each component type
		for (CompTypeID i = (CompTypeID)0; i < TOTAL_COMPONENT_TYPES; i = (CompTypeID)((int)i + 1)) {
			if (requiredComponents[i] && !entityComponents[i]) {
				// throw away and move to next entity
				continue;
			}
			else if (i == (CompTypeID)((int)TOTAL_COMPONENT_TYPES - 1)) {
				// add to list and move to next entity
				entities.push_back(e);
				continue;
			}
		}
	}
	return entities;
}

void Scene::DeleteEntity(EntityID entityID) {
	// delete entity Components
	DeleteComponents(GetEntityComponentSignature(entityID), entityID);

	// add ID to list of avaliable IDs
	oldEntityIDs.push(entityID);
	return;
}

template<typename T> T* Scene::GetComponent(EntityID entityID) {
	CompTypeID typeID = TypeToID<T>();
	if (HasComponent<T>(entityID)) {
		CompIndex index = componentIndexes[typeID][entityID];
		return static_cast<T*>(components[typeID][index]);
	}
	else return nullptr;
}

template<typename T> bool Scene::HasComponent(EntityID entityID) {
	CompTypeID typeID = TypeToID<T>();
	if (typeID == IDNotAComponent || componentIndexes[typeID][entityID] == NO_COMPONENT) {
		return false;
	}
	else return true;
}

bool Scene::HasComponent(CompTypeID requiredComponent, EntityID entityID) {
	if (componentIndexes[requiredComponent][entityID] == NO_COMPONENT) {
		return false;
	}
	else return true;
}

bool Scene::HasComponents(Signature requiredComponents, EntityID entityID) {//TODO: Make this work
	// for each component type
	for (CompTypeID i = (CompTypeID)0; i < TOTAL_COMPONENT_TYPES; i = (CompTypeID)(i + (CompTypeID)1)) {
		// if component type is in component signature
		if (requiredComponents[i]) {
			// if component type is not on entity
			if (!HasComponent(i, entityID)) {
				return false;
			}
		}
	}
	return true;
}

void Scene::DeleteComponents(Signature requiredComponents, EntityID entityID) {
	// for each component type
	for (CompTypeID i = (CompTypeID)0; i < TOTAL_COMPONENT_TYPES; i = (CompTypeID)(i + (CompTypeID)1)) {
		// if component type is in component signature
		if (requiredComponents[i]) {
			// if component type is on entity
			CompIndex index = componentIndexes[i][entityID];
			if (index != NO_COMPONENT) {
				// delete component
				delete components[i][index];
				components[i][index] = nullptr;
				// delete component index
				componentIndexes[i][entityID] = NO_COMPONENT;
				oldCompIndexes[i].push(index);
			}
		}
	}
	return;
}