#pragma once
#include "constants.h"
#include "raylib.h"
#include "types.h"
#include <cstdint>

//----------------------------------------------
// PHYSICS SYSTEM COMPONENTS:
//----------------------------------------------
struct PhysicsComponent{
    bool active[MAX_ENTITIES];
    Vector2 positions[MAX_ENTITIES];
    Vector2 velocities[MAX_ENTITIES];
    Vector2 sizes[MAX_ENTITIES];
    Vector2 forces[MAX_ENTITIES];
    float mass[MAX_ENTITIES];

};


//----------------------------------------------
// GAMEPLAY SYSTEM COMPONENTS:
//----------------------------------------------
struct StatsComponent{
    float hp[MAX_ENTITIES];
    float jumping_force[MAX_ENTITIES];
    float running_force[MAX_ENTITIES];

};

struct InputComponent{
    bool active[MAX_PLAYERS];
    MoveIntentHorizontal move_intent[MAX_PLAYERS];
    bool jump_pressed[MAX_PLAYERS];
    float coyote_timer[MAX_PLAYERS];
    float jump_buffer_timer[MAX_PLAYERS];
    bool run_pressed[MAX_PLAYERS];

};


//----------------------------------------------
// RENDER SYSTEM COMPONENTS:
//----------------------------------------------
struct RenderComponent{
    uint16_t asset_id[MAX_ENTITIES];
    uint16_t asset_width[MAX_ENTITIES];
    uint16_t asset_height[MAX_ENTITIES];

};

struct AnimationComponent{
    uint8_t n_frames[MAX_ENTITIES];
    uint8_t current_frame[MAX_ENTITIES];
    uint8_t asset_width[MAX_ENTITIES];
    uint8_t asset_height[MAX_ENTITIES];

    float timer[MAX_ENTITIES];
    float speed[MAX_ENTITIES];

    ActionState action_state[MAX_ENTITIES];
    Direction direction[MAX_ENTITIES];

};

//----------------------------------------------
// SOUND SYSTEM COMPONENTS:
//----------------------------------------------
struct SoundComponent{
    Music current_background_music;
    float current_music_volume;

};

