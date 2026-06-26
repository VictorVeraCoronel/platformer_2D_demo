#pragma once
#include "../../core/world.h"

void UpdateGameplay(World& world);

void OrderPhysicsFromInput(World& world, int i);

void UpdateAnimationState(World& world, int i);

void ResetOutOfBounds(World& world, int i);

void ClearInput(World& world,int i);
