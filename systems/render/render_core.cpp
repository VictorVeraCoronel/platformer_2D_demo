#include "../../core/world.h"
#include "render_core.h"
#include <raylib.h>
#include <iostream>

void RenderCore(World& world, Camera2D& camera){
    auto& renders = world.renders;
    auto& physics = world.physics;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(!renders.active[i]) continue;

        Rectangle rectangle = {physics.positions[i].x, physics.positions[i].y, 128 ,256};
        DrawRectangleRec(rectangle, RED);

    }

     RenderMap(world, camera);


}


void RenderMap(World& world, Camera2D& camera){

    auto& renders = world.renders;
    auto& level = world.current_level;


    float initial_x = (std::max(0, (static_cast<int>(camera.target.x - 1500)))) / (float)TILE_SIZE;
    float initial_y = (std::max(0, (static_cast<int>(camera.target.y - 1000)))) / (float)TILE_SIZE;

    //Determine how many tiles can fit into the screen
    int tiles_x = (GetScreenWidth() / TILE_SIZE) + 50; // This variable represents the number of tiles that you see in axis X
    int tiles_y = (GetScreenHeight() / TILE_SIZE) + 50; // This variable represents the number of tiles that you see in axis Y


    int index = 0;

    for (int y = initial_y; y < initial_y + tiles_y; y++) {
        for (int x = initial_x; x < initial_x  + tiles_x; x++) {

            int position_x = TILE_SIZE * x; // This variable represents the i index of the current tile being displayed
            int position_y = TILE_SIZE * y; // This variable represents the i index of the current tile being displayed
            Texture2D texture;
            index = y * world.current_level.width + x;

            texture = world.asset_repository.tile[0];

            // If the camera is out of bounds, do not draw anything
            if(position_x >= world.current_level.width * TILE_SIZE || position_y >= world.current_level.height * TILE_SIZE){
                continue;
            }
            if(position_x < 0 || position_y < 0){
                continue;
            }

            if(level.map[index] == 1){
                DrawTexture(texture, position_x, position_y, WHITE);
            }

        }
    }


}
