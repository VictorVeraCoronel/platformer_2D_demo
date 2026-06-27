#include "../../core/world.h"
#include "render_core.h"
#include <raylib.h>
#include <iostream>

void RenderCore(World& world, Camera2D& camera){

     RenderEntities(world);
     RenderMap(world, camera);


}

void RenderEntities(World& world){
    auto& renders = world.renders;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(!renders.active[i]) continue;

        auto& physics = world.physics;
        auto& anim = world.animations;
        auto& sprites = world.asset_repository.sprite;

        float width_sign = 1.0f; // 1.0f = Derecha, -1.0f = Izquierda

        if (physics.velocities[i].x > 10.0f) {
            width_sign = 1.0f;
        }
        else if (physics.velocities[i].x < -10.0f) {
            width_sign = -1.0f;
        }
        // SI EL PERSONAJE NO SE MUEVE HORIZONTALMENTE... PERO ESTÁ EN LA PARED:
        else if (physics.wall_collision[i] != WallCollision::NONE) {

            // Si la pared está a la DERECHA, el stickman debe mirar hacia la DERECHA (hacia el muro)
            if (physics.wall_collision[i] == WallCollision::RIGHT) {
                width_sign = 1.0f;
            }
            // Si la pared está a la IZQUIERDA, el stickman debe mirar hacia la IZQUIERDA
            else if (physics.wall_collision[i] == WallCollision::LEFT) {
                width_sign = -1.0f;
            }
        }


        float source_x = anim.current_frame[i] * renders.asset_width[i];
        float source_y = (float)anim.state[i] * renders.asset_height[i];
        Rectangle source_rec = { source_x, source_y, (float)renders.asset_width[i] * width_sign, (float)renders.asset_height[i] };

        Texture2D texture = sprites[renders.asset_id[i]];
        Rectangle dest_rec = { physics.positions[i].x, physics.positions[i].y, (float)renders.asset_width[i], (float)renders.asset_height[i] };
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(texture, source_rec, dest_rec, origin, 0.0f, WHITE);

    }

}


void RenderMap(World& world, Camera2D& camera){

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
