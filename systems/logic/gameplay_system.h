#pragma once
#include "../../core/world.h"

void UpdateGameplay(World& world, float dt);

// GENERAL GAMEPLAY FUNCTIONS

void ApplyPendingDamage(World& world, float dt);



// ENTITIES GAMEPLAY FUNCTIONS

void UpdateEntityBehaviour(World& world);

void UpdateEntityAnimations(World& world);



// PLAYERS GAMEPLAY FUNCTIONS

void OrderPhysicsFromInput(World& world);

void UpdateAnimationState(World& world);

void ResetOutOfBounds(World& world);

void ResetIfDead(World& world);

void ClearInput(World& world);
