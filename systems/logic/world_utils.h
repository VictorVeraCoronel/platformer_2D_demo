#pragma once
#include "../../core/world.h"
#include <raylib.h>

uint16_t GetClosestPlayerIndex(const World& world, Vector2 from_position);

void KillEntity(World& world, int i);
