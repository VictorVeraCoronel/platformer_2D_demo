#include "raylib.h"
#include <cmath>
#include "./camera_manager.h"
#include "../../core/world.h"


void FollowCamera(World &world, Camera2D &camera, float dt){

    //We create a Lerp factor.
    float follow_slower = 0.13f;
    float lerp_factor = 1.0f - pow(follow_slower, dt);


    if(std::abs(world.physics.positions[0].x - camera.target.x) < 10.0f && std::abs(world.physics.positions[0].y - camera.target.y) < 10.0f){
        camera.target = (Vector2){ camera.target.x , camera.target.y };

    }else{
        camera.target = (Vector2){ camera.target.x + (world.physics.positions[0].x - camera.target.x) * lerp_factor, camera.target.y + (world.physics.positions[0].y - camera.target.y) * lerp_factor };
    }
}


void InitCameraManager(World &world, Camera2D &camera){

    camera.target = (Vector2){ world.physics.positions[0].x, world.physics.positions[0].y};
    camera.zoom = 0.66f;
    camera.offset = (Vector2){ 1920.0f/2-64, 1080.0f/2.33-64 };
}
