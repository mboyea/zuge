#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#define NOMINMAX
#include <limits>
#include <cstdint>

typedef std::int32_t EntityID;

// Maximum number of entities allowed in a scene
const EntityID MAX_ENTITIES = std::numeric_limits<EntityID>::max();

const EntityID NO_ENTITY = -1;

#endif // ENTITY_H