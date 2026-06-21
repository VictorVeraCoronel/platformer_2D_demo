#include <memory>
#include "./core/world.h"
#include "./systems/logic/physics_system.h"
#include "./systems/logic/gameplay_system.h"
#include "./systems/logic/input_system.h"

int main(){

    std::unique_ptr<World> world = std::make_unique<World>();

    InitWindow(1280, 720, "platformer_2D");
    SetTargetFPS(144.0f);

    const float dt = 1.0f / 60.0f; //
    float acumulador = 0.0f;

    while (!WindowShouldClose()) {

        float frame_time = GetFrameTime();

        if (frame_time > 0.25f) frame_time = 0.25f;

        acumulador += frame_time;

        // LOGIC LOOP (60 HZ)
        while (acumulador >= dt) {

            UpdateInput(*world);
            UpdatePhysics(*world, dt);
            UpdateGameplay(*world);

            acumulador -= dt;
        }

        // RENDER LOOP (144 HZ)
        BeginDrawing();
        ClearBackground(RAYWHITE);

            //RenderCoreSystem(world);
            //RenderUISystem(world);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
