#include "../../core/world.h"
#include "render_core.h"
#include <raylib.h>
#include <iostream>

void RenderCore(World& world, Camera2D& camera){
    auto& renders = world.renders;
    auto& physics = world.physics;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(!renders.active[i]) continue;

        //Useful data references
        float& pos_x = physics.positions[i].x;
        float& pos_y = physics.positions[i].y;
        float width = (float)renders.asset_width[i];
        float height = (float)renders.asset_height[i];

        //Draw rectangle in entity position of entity proportions
        Rectangle rectangle = {pos_x, pos_y, width ,height};
        DrawRectangleRec(rectangle, RED);

    }

     RenderMap(world, camera);


}


void RenderMap(World& world, Camera2D& camera){

    auto& renders = world.renders;
    auto& level = world.current_level;


    //Determine initial tile_x and initial tile_y of the camera.
    int initial_x = (std::max(0, (static_cast<int>(camera.target.x - 1500)))) / (int)TILE_SIZE;
    int initial_y = (std::max(0, (static_cast<int>(camera.target.y - 1000)))) / (int)TILE_SIZE;

    //Determine how many tiles can fit into the screen
    int tiles_x = ((GetScreenWidth()) / TILE_SIZE) + 64; // This variable represents the number of tiles that you see in axis X
    int tiles_y = ((GetScreenHeight()) / TILE_SIZE) + 64; // This variable represents the number of tiles that you see in axis Y


    for (int y = initial_y; y < initial_y + tiles_y; y++) {
        for (int x = initial_x; x < initial_x  + tiles_x; x++) {

            Texture2D texture = world.asset_repository.tile[0];
            int position_x = TILE_SIZE * x;
            int position_y = TILE_SIZE * y;
            int index = (y * level.width) + (x);

            // If the camera is out of bounds, do not draw anything
            if(position_x >= level.width * TILE_SIZE || position_y >= level.height * TILE_SIZE){
                continue;
            }
            if(position_x < 0 || position_y < 0){
                continue;
            }

            if(level.map[index] != 0){
                DrawTexture(texture, position_x, position_y, WHITE);
            }

        }
    }


}
