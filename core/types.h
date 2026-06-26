#pragma once
#include <cstdint>
#include <vector>
#include "constants.h"
#include "raylib.h"
#include <string>


//----------------------------------------------
// WORLD CUSTOM TYPES:
//----------------------------------------------
enum class MoveIntentHorizontal : int8_t {
    LEFT = -1,
    NONE = 0,
    RIGHT = 1
};

enum class WallCollision : int8_t{
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

enum class GameState : uint8_t {
    MAIN_MENU = 0,
    GAMEPLAY = 1,
    PAUSE = 2,
    GAME_OVER = 3
};



//----------------------------------------------
// WORLD DATA STRUCTURES:
//----------------------------------------------
struct Level{
    uint16_t width;
    uint16_t height;
    Vector2 respawn_point;

    std::vector<uint8_t> map;

    inline uint16_t GetTileIndexAtPosition(float pixel_x, float pixel_y) const {

        // Negative pixels are out of bounds
        if (pixel_x < 0.0f || pixel_y < 0.0f) return 0;

        // We determine tile cells using the pixels and tile size
        int cell_x = static_cast<int>(pixel_x) / TILE_SIZE;
        int cell_y = static_cast<int>(pixel_y) / TILE_SIZE;

        // Security check for out of bounds
        if (cell_x >= width || cell_y >= height) {
            return 0;
        }

        // Calculate index of the map
        return ((cell_y * width) + cell_x);
    }

    inline uint8_t GetTileValueAtPosition(float pixel_x, float pixel_y) {
        // Negative pixels are out of bounds
        if (pixel_x < 0.0f || pixel_y < 0.0f) return 0;

        // We determine tile cells using the pixels and tile size
        int cell_x = static_cast<int>(pixel_x) / TILE_SIZE;
        int cell_y = static_cast<int>(pixel_y) / TILE_SIZE;

        // Security check for out of bounds
        if (cell_x >= width || cell_y >= height) {
            return 0;
        }

        // Calculate index of the map
        int index = (cell_y * width) + cell_x;

        // Return map value at index
        return map[index];
    }

};

struct AssetRepository{
    Texture2D sprite[MAX_ASSETS];
    Texture2D tile[MAX_ASSETS];
    Texture2D ui[MAX_ASSETS];
    Texture2D wallpaper[MAX_ASSETS];

};

struct Entity{
    float jumping_force;
    float running_force;
    float wall_jumping_force;
    float air_movement_force;
    float HP;
    float anim_speed;
    float mass;
    float aggro_range;

    uint16_t sprite_id;
    uint16_t sprite_width;
    uint16_t sprite_height;
    uint16_t width;
    uint16_t height;
    uint8_t n_animation_frames;

    AIArchetype ai_archetype;
};

struct VirtualScreen{

    int width;
    int height;

    // Middleman texture before rendering to real screen
    RenderTexture2D target_render_texture;


};
