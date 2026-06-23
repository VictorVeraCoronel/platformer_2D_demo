#include <cmath>
#include <memory>
#include "./core/world.h"
#include "./systems/logic/physics_system.h"
#include "./systems/logic/gameplay_system.h"
#include "./systems/logic/input_system.h"
#include "./systems/render/render_core.h"
#include "./systems/render/camera_manager.h"

#include "core/types.h"
#include "loaders/data_loader.h"
#include "loaders/asset_loader.h"

#include <iostream>
#include <raylib.h>

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
    InitWindow(1600, 900, "platformer_2D");
    SetTargetFPS(60.0f);

    //initialization
    Camera2D camera = { 0 };
    std::unique_ptr<World> world = std::make_unique<World>();
    LoadGameData(*world);

    InitCameraManager(*world, camera);

    const float dt = 1.0f / 60.0f; //
    float acumulador = 0.0f;

    VirtualScreen virtual_screen;
    virtual_screen.width = 1920;
    virtual_screen.height = 1080;
    virtual_screen.target_render_texture = LoadRenderTexture(1920, 1080);



    while (!WindowShouldClose()) {
        //std::cout<<world->current_level.map[0]<<std::endl;

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


        // // RENDER LOOP (144 HZ)
        // BeginDrawing();
        // ClearBackground(RAYWHITE);
        //
        //     RenderCore(*world);
        //     //RenderUISystem(world);
        //
        // EndDrawing();


        // RENDER LOOP (144 HZ)
        BeginTextureMode(virtual_screen.target_render_texture);
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                FollowCamera(*world, camera, dt);
                RenderCore(*world);

            EndMode2D();

        EndTextureMode();


        //Now we apply the scale to the virtual texture and draw it after scaling it correctly
        BeginDrawing();
        ClearBackground(BLACK);

        // Calculate the scale
        float scale = fminf((float)GetScreenWidth() / virtual_screen.width,
                            (float)GetScreenHeight() / virtual_screen.height);

        // We draw the virtual texture
        DrawTexturePro(
            virtual_screen.target_render_texture.texture,
            // Origen: La textura de Raylib está invertida en el eje Y por convención de OpenGL, usamos el menos (-)
            Rectangle{ 0.0f, 0.0f, (float)virtual_screen.target_render_texture.texture.width, (float)-virtual_screen.target_render_texture.texture.height },
                       // Destino: Centrado en la pantalla real actual del cliente
                       Rectangle{
                           ((float)GetScreenWidth() - ((float)virtual_screen.width * scale)) * 0.5f,
                       ((float)GetScreenHeight() - ((float)virtual_screen.height * scale)) * 0.5f,
                       (float)virtual_screen.width * scale,
                       (float)virtual_screen.height * scale
                       },
                       Vector2{ 0, 0 },
                       0.0f,
                       WHITE
        );
        EndDrawing();
    }


    CloseWindow();
    return 0;
}
