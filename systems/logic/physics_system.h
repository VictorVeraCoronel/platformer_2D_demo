#pragma once
#include "../../core/world.h"

void IntegrateForces(World& world, float dt);

void ResolveXCollisions(World& world, float dt);

void ResolveYCollisions(World& world, float dt);

void EnemyCollisions(World& world, float dt);

void ApplyFrictions(World& world, float dt);

void UpdatePhysics(World& world, float dt);
