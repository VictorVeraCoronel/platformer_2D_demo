#include <memory>
#include "./core/world.h"
#include "./systems/logic/physics_system.h"
#include "./systems/logic/gameplay_system.h"
#include "./systems/logic/input_system.h"

#include "./systems/render/render_core.h"

#include "core/constants.h"
#include "loaders/data_loader.h"
#include "loaders/asset_loader.h"

#include <iostream>

void LoadGameData(World& world){

    LoadPlayerData(world);
    LoadEnemiesData(world, "world_1");
    LoadBossesData(world, "world_1");

    LoadUIAssets(world);
    LoadSpriteAssets(world);
    LoadTileAssets(world);

    LoadLevelData(world, "world_1", "level_1");
}

int main(){

    std::unique_ptr<World> world = std::make_unique<World>();
    LoadGameData(*world);

    //Testing
    // world->physics.active[0] = true;
    // world->stats.active[0] = true;
    // world->inputs.active[0] = true;
    // world->renders.active[0] = true;
    // world->physics.positions[0].x = 50.0f;
    // world->physics.positions[0].y = 50.0f;
    // world->physics.mass[0] = 1;
    // world->stats.jumping_force[0] = 60000.0f;
    // world->stats.running_force[0] = 7500.0f;
    // world->stats.air_movement_force[0] = 1000.0f;

    std::cout<<world->physics.active[0]<<std::endl;
    std::cout<<world->stats.active[0]<<std::endl;
    std::cout<<world->inputs.active[0]<<std::endl;
    std::cout<<world->renders.active[0]<<std::endl;

    std::cout<<world->physics.positions[0].x<<std::endl;
    std::cout<<world->physics.positions[0].y<<std::endl;


    std::cout<<world->physics.active[MAX_PLAYERS]<<std::endl;
    std::cout<<world->stats.active[MAX_PLAYERS]<<std::endl;
    std::cout<<world->renders.active[MAX_PLAYERS]<<std::endl;

    std::cout<<world->physics.positions[MAX_PLAYERS].x<<std::endl;
    std::cout<<world->physics.positions[MAX_PLAYERS].y<<std::endl;





    InitWindow(1600, 900, "platformer_2D");
    SetTargetFPS(60.0f);

    const float dt = 1.0f / 60.0f; //
    float acumulador = 0.0f;




    while (!WindowShouldClose()) {

        float frame_time = GetFrameTime();

        if (frame_time > 0.25f) frame_time = 0.25f;

        acumulador += frame_time;


        UpdateInput(*world);
        // LOGIC LOOP (60 HZ)
        while (acumulador >= dt) {

            UpdatePhysics(*world, dt);
            UpdateGameplay(*world);

            acumulador -= dt;
        }

        // RENDER LOOP (144 HZ)
        BeginDrawing();
        ClearBackground(RAYWHITE);

            RenderCore(*world);
            //RenderUISystem(world);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
