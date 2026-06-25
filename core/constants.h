#pragma once
#include <cstdint>


//----------------------------------------------
// DATA THAT WILL ALWAYS BE THE SAME THROUGHOUT THE ENTIRE GAME:
//----------------------------------------------
const uint16_t MAX_ENTITIES = 500;
const uint8_t MAX_PLAYERS = 5;
const uint8_t MAX_ASSETS = 100;
const uint8_t MAX_DATA = 100;
const float GROUND_FRICTION = 0.85;
const float WALL_FRICTION = 0.5f;
const float AIR_FRICTION = 0.98f;
const uint8_t TILE_SIZE = 64;
