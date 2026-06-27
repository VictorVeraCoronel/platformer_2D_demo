#pragma once
#include "constants.h"
#include "raylib.h"
#include "types.h"
#include <cstdint>

//----------------------------------------------
// PHYSICS SYSTEM COMPONENTS:
//----------------------------------------------
struct PhysicsComponent{
    bool active[MAX_ENTITIES] = {};
    Vector2 positions[MAX_ENTITIES] = {};
    Vector2 velocities[MAX_ENTITIES] = {};
    Vector2 sizes[MAX_ENTITIES] = {};
    Vector2 forces[MAX_ENTITIES] = {};
    float mass[MAX_ENTITIES] = {};
    bool is_grounded[MAX_ENTITIES] = {};
    WallCollision wall_collision[MAX_ENTITIES] = {};
    float coyote_timer[MAX_ENTITIES] = {};//Jump grace time

    // Components that will interact with other systems, such as gameplay
    Vector2 desired_positions[MAX_ENTITIES] = {};
    bool has_desired_position[MAX_ENTITIES] = {};

};


//----------------------------------------------
// GAMEPLAY SYSTEM COMPONENTS:
//----------------------------------------------
struct StatsComponent{
    bool active[MAX_ENTITIES] = {};
    float hp[MAX_ENTITIES] = {};


};

struct LocomotionComponent{
    bool active[MAX_PLAYERS] = {};
    float jumping_force[MAX_PLAYERS] = {};
    float wall_jumping_force[MAX_PLAYERS] = {};
    float running_force[MAX_PLAYERS] = {};
    float air_movement_force[MAX_PLAYERS] = {};
};

struct AIComponent{
    bool active[MAX_ENTITIES] = {};
    AIArchetype ai_arquetypes[MAX_ENTITIES] = {};
    AIState ai_states[MAX_ENTITIES] = {};
    float aggro_range[MAX_ENTITIES] = {};
    float follow_speed[MAX_ENTITIES] = {};
    float patrol_speed[MAX_ENTITIES] = {};

};

struct InputComponent{
    bool active[MAX_PLAYERS] = {};
    MoveIntentHorizontal move_intent[MAX_PLAYERS] = {};
    bool jump_pressed[MAX_PLAYERS] = {};
    bool jump_released[MAX_PLAYERS] = {};
    float jump_buffer_timer[MAX_PLAYERS] = {};
    bool run_pressed[MAX_PLAYERS] = {};
    float horizontal_lock_timer[MAX_PLAYERS] = {};

};


//----------------------------------------------
// RENDER SYSTEM COMPONENTS:
//----------------------------------------------
struct RenderComponent{
    bool active[MAX_ENTITIES] = {};
    uint16_t asset_id[MAX_ENTITIES] = {};
    uint16_t asset_width[MAX_ENTITIES] = {};
    uint16_t asset_height[MAX_ENTITIES] = {};

};

struct AnimationComponent{
    float anim_speed[MAX_ENTITIES] = {};
    uint8_t n_frames[MAX_ENTITIES] = {};


    bool active[MAX_ENTITIES] = {};
    float timer[MAX_ENTITIES] = {};
    uint8_t current_frame[MAX_ENTITIES] = {};
    AnimState state[MAX_ENTITIES] = {};
    AnimDirection direction[MAX_ENTITIES] = {};

};

//----------------------------------------------
// SOUND SYSTEM COMPONENTS:
//----------------------------------------------
struct SoundComponent{
    bool active[MAX_ENTITIES] = {};
    Music current_background_music;
    float current_music_volume = 0.5f;

    SoundEvent sound_trigger_id[MAX_ENTITIES] = {};
    bool should_play[MAX_ENTITIES] = {};

};

