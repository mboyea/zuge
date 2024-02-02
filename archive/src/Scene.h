#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "Components.h"
#include "Systems.h"
#include "Entity.h"
#include <array>
#include <vector>
#include <set>
#include <queue>

#include <iostream>

class Scene {
private:
	// An array of arrays of indexes into the component arrays, acquired via Entities and Component Types
	// Y - std::array of sets with each element position being representative of a Component Type ID
	// & each element value being X
	// X - std::vector of indexes with each element position being representative of an Entity ID
	// & each element value being representative of the position of the component in the component container(components)
	/****EXAMPLE:****
	  _E0_E1_E2_E3_   E = Entity ID | C = Component ID | i = Index
	C0|i0|i1|~~|i2|     **A ~~ IS REPRESENTATIVE OF A NULL/NAN VALUE (of actual value equal to -1)**
	  |--+--+--+--+-    Entity 0 has only Component 0 at index 0
	C1|~~|~~|i0|i1|     Entity 1 has Components 0(indx1) and 2(indx0)
	  |--+--+--+--+-    Entity 2 has only Component 1(indx0)
	C2|~~|i0|~~|i1|     Entity 3 has Components 0(indx2), 1(indx1), and 2(indx1)
	****************/
	std::array<std::vector<CompIndex>, TOTAL_COMPONENT_TYPES> componentIndexes;

	// An array of vectors of Component*s, holding each components' data, acquired via Index & Component Type
	// Y - std::array of vectors with each element position being representative of a Component Type
	// & each element value being X
	// X - std::vector of Component*s with each element position being indexed into via Entity IDs
	// & each element value holding the data concerning a certain component
	/****EXAMPLE:****
	  _i0_i1_i2_i3_	  CD = Component Data | C = Component ID | i = Index
	C0|CD|CD|CD|~~|		Component 0 has 3 components
	  |--+--+--+--+-
	C1|CD|CD|~~|~~|		Component 1 has 2 components
	  |--+--+--+--+-
	C2|CD|CD|~~|~~| 	Component 2 has 2 components
	****************/
	std::array<std::vector<Component*>, TOTAL_COMPONENT_TYPES> components;

	std::queue<EntityID> oldEntityIDs;
	std::array<std::queue<CompIndex>, TOTAL_COMPONENT_TYPES> oldCompIndexes;
	EntityID GetEntityIDCount();
	EntityID GenerateNewEntityID();
	CompIndex GenerateNewCompIndex(CompTypeID compType);
public:
	Scene();

	void Update();

	EntityID NewEntity();
	EntityID NewEntity(std::string entityName);
	EntityID GetEntityID(std::string entityName);
	Signature GetEntityComponentSignature(EntityID entityID);
	std::vector<EntityID> GetEntitiesWithComponents(Signature requiredComponents);
	void DeleteEntity(EntityID entityID);
	
	template<typename T> T* AddComponent(EntityID entityID) {
		// Error Lnk2019 when defined inside Scene.cpp
		// Leave here for now.

		// get component type ID
		CompTypeID typeID = TypeToID<T>();
		if (typeID == IDNotAComponent || componentIndexes[typeID][entityID] != NO_COMPONENT) {
			return nullptr;
		}
		else {
			// generate component index
			CompIndex index = GenerateNewCompIndex(typeID);
			componentIndexes[typeID][entityID] = index;
			// populate component data
			if (index + 1 > (EntityID)components[typeID].size()) {
				components[typeID].resize(index + 1, nullptr);
			}
			// create new component
			components[typeID][index] = new T;
			return static_cast<T*>(components[typeID][index]);
		}
		return nullptr;
	}
	template<typename T> T* GetComponent(EntityID entityID);
	template<typename T> bool HasComponent(EntityID entityID);
	bool HasComponent(CompTypeID requiredComponent, EntityID entityID);
	bool HasComponents(Signature requiredComponents, EntityID entityID);
	template<typename T> void DeleteComponent(EntityID entityID) {
		// Error Lnk2019 when defined inside Scene.cpp
		// Leave here for now.

		CompTypeID typeID = TypeToID<T>();
		CompIndex index = componentIndexes[typeID][entityID];
		if (typeID == IDNotAComponent || index == NO_COMPONENT) {
			return;
		}
		else {
			// delete component
			delete components[typeID][index];
			components[typeID][index] = nullptr;
			// delete component index
			componentIndexes[typeID][entityID] = NO_COMPONENT;
			oldCompIndexes[typeID].push(index);
			return;
		}
	}
	void DeleteComponents(Signature requiredComponents, EntityID entityID);
};

#endif // SCENE_H