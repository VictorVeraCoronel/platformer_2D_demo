#pragma once
#include "raylib.h"
#include "../core/world.h"

void SpawnEntity(World& world, std::string entity_type, Vector2 position, uint16_t id);
