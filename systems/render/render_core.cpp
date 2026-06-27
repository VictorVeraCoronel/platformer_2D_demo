#include "../../core/world.h"
#include "render_core.h"
#include "render_entities.h"
#include "render_map.h"
#include <raylib.h>

void RenderCore(const World& world, Camera2D& camera, const VirtualScreen& virtual_screen){

    // RENDER THE WORLD IN THE VIRTUAL TEXTURE                                               |
    BeginTextureMode(virtual_screen.target_render_texture);
        ClearBackground(RAYWHITE);


        BeginMode2D(camera);

            RenderBackground(world, camera);
            RenderEntities(world);
            RenderMap(world, camera, virtual_screen);

        EndMode2D();

    EndTextureMode();



    // DRAW VIRTUAL TEXTURE IN THE MONITOR                                                   |
    BeginDrawing();
        ClearBackground(BLACK);

        // CALCULATE DYNAMIC SCALE DEPENDING ON USER SCREEN RESOLUTION
        float scale = fminf((float)GetScreenWidth() / virtual_screen.width,
                            (float)GetScreenHeight() / virtual_screen.height);

        DrawTexturePro(
            virtual_screen.target_render_texture.texture,
            // ORIGIN: RAYLIB'S Y AXIS TEXTURE IS INVERTED BY OPENGL CONVENTION, THATS WHY WE USE (-)
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




        // ---------------------------------------------------------------------------------------
        // DEBUG CONSOLE PRINTS                                                                  |
        // ---------------------------------------------------------------------------------------
        const std::string pos_x = "Position_x: " + std::to_string(world.physics.positions[0].x);
        const std::string pos_y = "Position_y: " + std::to_string(world.physics.positions[0].y);
        DrawText(pos_x.c_str() ,2, 990, 32, BLACK);
        DrawText(pos_y.c_str() ,2, 1042, 32, BLACK);
        // ---------------------------------------------------------------------------------------
        // DEBUG CONSOLE PRINTS                                                                  |
        // ---------------------------------------------------------------------------------------



    EndDrawing();

}

VirtualScreen LoadVirtualScreen(int v_screen_width, int v_screen_height, int texture_width, int texture_height){
    VirtualScreen virtual_screen;

    virtual_screen.width = v_screen_width;
    virtual_screen.height = v_screen_height;
    virtual_screen.target_render_texture = LoadRenderTexture(texture_width, texture_height);

    return virtual_screen;
}
