#pragma once
#include "../../core/world.h"

void IntegrateForces(World& world, float dt, uint16_t i);

void ResolveXCollisions(World& world, float dt, uint16_t i);

void ResolveYCollisions(World& world, float dt, uint16_t i);

void ApplyFrictions(World& world, float dt, uint16_t i);

void UpdatePhysics(World& world, float dt);
