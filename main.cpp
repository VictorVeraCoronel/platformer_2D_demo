#include <memory>
#include "./core/world.h"
#include "./systems/logic/physics_system.h"
#include "./systems/logic/gameplay_system.h"
#include "./systems/logic/input_system.h"
#include "./systems/logic/animation_system.h"
#include "./systems/render/render_core.h"
#include "./systems/render/camera_manager.h"

#include "core/types.h"
#include "loaders/data_loader.h"
#include "loaders/asset_loader.h"
#include "systems/logic/ai_system.h"

#include <raylib.h>

void LoadGameData(World& world){
    LoadAllData(world, "world_1", "level_1");
    LoadAllAssets(world);
    InstantiateLevel(world, "world_1", "level_1");
}

void InitRaylibWindow(){
    InitWindow(1920, 1080, "platformer_2D");
    ToggleBorderlessWindowed();
    SetTargetFPS(144.0f);
}

int main(){

    // GRAPHIC INITIALIZATION
    InitRaylibWindow();
    Camera2D camera = {0, 0, 0, 0, 0, 0};
    VirtualScreen virtual_screen = LoadVirtualScreen(1920, 1080, 1920, 1080);

    // LOGIC INITIALIZATION
    std::unique_ptr<World> world = std::make_unique<World>();
    LoadGameData(*world);
    InitCameraManager(*world, camera);
    const float dt = 1.0f / 144.0f;
    float acumulador = 0.0f;


    // GAME LOOP
    while (!WindowShouldClose()) {

        // FIXED DELTA TIME SYNC
        float frame_time = GetFrameTime();
        if (frame_time > 0.25f) frame_time = 0.25f; //CLAMPING TO AVOID DEATH SPIRAL
        acumulador += frame_time;


        // FIXED LOGIC LOOP (144 HZ)
        while (acumulador >= dt) {
            UpdateInput(*world, dt);
            UpdateAnimationSystem(*world, dt);
            UpdateAISystem(*world);
            UpdateGameplay(*world);
            UpdatePhysics(*world, dt);
            FollowCamera(*world, camera, dt);

            acumulador -= dt;
        }


        // FRAME RENDER
        RenderCore(*world, camera, virtual_screen);

    }




    CloseWindow();
    return 0;
}
