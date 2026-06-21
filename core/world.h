#pragma once
#include "./components.h"
#include "types.h"
#include <unordered_map>

struct World{

    //----------------------------------------------
    // COMPONENTS:
    //----------------------------------------------
    PhysicsComponent physics = {};
    StatsComponent stats = {};
    InputComponent inputs = {};
    RenderComponent renders = {};
    AnimationComponent animations = {};
    SoundComponent sounds = {};

    //----------------------------------------------
    // WORLD ATTRIBUTES:
    //----------------------------------------------
    Level current_level;
    AssetRepository asset_repository;
    std::unordered_map<std::string, Entity> entity_repository;
    float gravity = 1600.0f;
    float fall_gravity_multiplier = 2.25f;

    //----------------------------------------------
    // Init of every world attribute:
    //----------------------------------------------
    World() = default;

};
