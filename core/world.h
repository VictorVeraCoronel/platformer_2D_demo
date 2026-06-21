#pragma once
#include "./components.h"
#include "types.h"

struct World{

    //----------------------------------------------
    // COMPONENTS:
    //----------------------------------------------
    PhysicsComponent physics;
    StatsComponent stats;
    InputComponent inputs;
    RenderComponent renders;
    AnimationComponent animations;
    SoundComponent sounds;

    //----------------------------------------------
    // WORLD ATTRIBUTES:
    //----------------------------------------------
    Level current_level;
    AssetRepository asset_repository;
    EntityRepository entity_repository;
    float gravity = 9.8f;
    float fall_gravity_multiplier = 1.5f;

    //----------------------------------------------
    // Init of every world attribute:
    //----------------------------------------------
    World(){

    }

};
