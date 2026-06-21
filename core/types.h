#pragma once
#include <cstdint>
#include <vector>
#include "constants.h"
#include "raylib.h"


//----------------------------------------------
// WORLD CUSTOM TYPES:
//----------------------------------------------
enum class MoveIntentHorizontal : int8_t {
    LEFT = -1,
    NONE = 0,
    RIGHT = 1
};

enum class AIArchetype : uint8_t {
    MELEE_CHASER = 0,
    RANGED_KITER = 1
};

enum class ActionState : uint8_t {
    IDLE = 0,
    RUNNING = 1,
    ATTACKING = 2,
    JUMPING = 3,
    FALLING = 4,
    WALL_SLIDING = 5
};

enum class Direction : uint8_t {
    LEFT = 0,
    RIGHT = 1

};

enum class SoundEvent : uint8_t {
    NONE = 0,
    PLAYER_JUMP=1,
    PLAYER_HIT=2,
    ENEMY_DEATH=3,
    COIN_PICKUP=4,
    WALL_SLIDE_LOOP=5
};



//----------------------------------------------
// WORLD DATA STRUCTURES:
//----------------------------------------------
struct Level{
    uint16_t width;
    uint16_t height;

    std::vector<int8_t> map;

};

struct AssetRepository{
    Texture2D sprite[MAX_ASSETS];
    Texture2D tile[MAX_ASSETS];
    Texture2D ui[MAX_ASSETS];

};

struct EntityRepository{
    float jumping_force[MAX_ASSETS];
    float running_force[MAX_ASSETS];
    float HP[MAX_ASSETS];

    uint16_t sprite_id[MAX_ASSETS];
    uint16_t sprite_width[MAX_ASSETS];
    uint16_t sprite_height[MAX_ASSETS];
    uint8_t n_animation_frames[MAX_ASSETS];

    AIArchetype ai_archetype[MAX_ASSETS];

};
