#include "render_map.h"
#include <algorithm>

void RenderMap(const World& world, Camera2D& camera, const VirtualScreen& virtual_screen){

    auto& level = world.current_level;

    // DETERMINE INITIAL COL AND INITIAL ROW (X, Y)
    int initial_x = (std::max(0, (static_cast<int>(camera.target.x - 1500)))) / (int)TILE_SIZE;
    int initial_y = (std::max(0, (static_cast<int>(camera.target.y - 1000)))) / (int)TILE_SIZE;

    // DETERMINE HOW MANY TILES CAN FIT IN THE SCREEN
    int tiles_x = (virtual_screen.width / TILE_SIZE) + 20; // NUMBER OF TILES YOU SEE IN AXIS X
    int tiles_y = (virtual_screen.height / TILE_SIZE) + 20; // NUMBER OF TILES YOU SEE IN AXIS Y

    // DETERMINE FINAL COL AND FINAL ROW (X, Y)
    int end_x = std::min((int)level.width, initial_x + tiles_x);
    int end_y = std::min((int)level.height, initial_y + tiles_y);


    // For now, this texture is loaded once, in the future, it will be variable inside the loop below
    Texture2D texture = world.asset_repository.tile[0];

    for (int y = initial_y; y < end_y; y++) {
        for (int x = initial_x; x < end_x; x++) {

            int position_x = TILE_SIZE * x;
            int position_y = TILE_SIZE * y;
            int index = (y * level.width) + (x);


            // DRAW MAP WHEN IT EXISTS
            if(level.map[index] != 0){
                DrawTexture(texture, position_x, position_y, WHITE);
            }

        }
    }


}

void RenderBackground(const World& world, Camera2D& camera){

    float fondo_x = camera.target.x * 0.2f;
    float fondo_y = camera.target.y * 0.2f;

    for (int i = -1; i < 5; i++) {

        for(int j = -1; j < 5; j++){
            float ancho_fondo = 3840.0f;
            float alto_fondo = 2160.0f;
            DrawTexture(world.asset_repository.wallpaper[0], fondo_x + (i * ancho_fondo), fondo_y + (j * alto_fondo), WHITE);
        }

    }
}
