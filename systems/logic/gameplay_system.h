#pragma once
#include "../../core/world.h"

void UpdateGameplay(World& world);

// ENTITIES GAMEPLAY FUNCTIONS

void UpdateEntityBehaviour(World& world, int i, int player_index);

void UpdateEntityAnimations(World& world, int i);


// PLAYERS GAMEPLAY FUNCTIONS

void OrderPhysicsFromInput(World& world, int i);

void UpdateAnimationState(World& world, int i);

void ResetOutOfBounds(World& world, int i);

void ClearInput(World& world,int i);
