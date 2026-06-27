#pragma once
#include "../../core/world.h"
#include <raylib.h>

int16_t GetClosestPlayerIndex(const World& world, Vector2 from_position);
