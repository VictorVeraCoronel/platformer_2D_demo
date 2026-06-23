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

    std::vector<uint8_t> map;

    inline Vector2 GetTileCoords(float world_x, float world_y) const {
        return Vector2{
            static_cast<float>(static_cast<int>(world_x / TILE_SIZE)),
            static_cast<float>(static_cast<int>(world_y / TILE_SIZE))
        };
    }

    inline Vector2 TileIndexToVector2(uint16_t index) const {
        uint16_t row = index / width;
        uint16_t col = index % width;

        return Vector2{
            static_cast<float>(static_cast<int>(col * TILE_SIZE)),
            static_cast<float>(static_cast<int>(row * TILE_SIZE))
        };
    }

    inline uint8_t GetTileAtPosition(float x, float y) const {
        if (x < 0 || x >= width*TILE_SIZE || y < 0 || y >= height*TILE_SIZE) {
            return 0;
        }

        return (y * width) + x;
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
