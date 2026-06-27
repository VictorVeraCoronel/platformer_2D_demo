#include "asset_loader.h"
#include "../core/world.h"
#include <fstream>
#include <string>
#include "../dependencies/json.hpp"


// Internal auxiliar function
void LoadTextureCategory(Texture2D* target_array, const std::string& json_path, const std::string& asset_key) {
    std::ifstream file(json_path, std::ifstream::binary);
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo de assets: " << json_path << std::endl;
        return;
    }

    nlohmann::json json_data;
    file >> json_data;

    // Iterate depending on map key (ui_assets, sprites_assets, etc.)
    for (const auto& item : json_data[asset_key]) {
        for (auto it = item.begin(); it != item.end(); ++it) {
            int id = std::stoi(it.key());
            std::string path = it.value();

            // We load the texture directly into the target array
            target_array[id] = LoadTexture(path.c_str());
        }
    }
}

void LoadUIAssets(World& world) {
    LoadTextureCategory(world.asset_repository.ui, "./game_data/textures/ui.json", "ui_assets");
    std::cout<<"Assets de ui cargadas con exito"<<std::endl;
}

void LoadSpriteAssets(World& world) {
    LoadTextureCategory(world.asset_repository.sprite, "./game_data/textures/sprites.json", "sprites_assets");
    std::cout<<"Assets de sprites cargadas con exito"<<std::endl;
}

void LoadTileAssets(World& world) {
    LoadTextureCategory(world.asset_repository.tile, "./game_data/textures/tiles.json", "tiles_assets");
    std::cout<<"Assets de tiles cargadas con exito"<<std::endl;
}

void LoadWallpaperAssets(World& world) {
    LoadTextureCategory(world.asset_repository.wallpaper, "./game_data/textures/wallpapers.json", "wallpaper_assets");
    std::cout<<"Assets de wallpapers cargadas con exito"<<std::endl;
}

void LoadAllAssets(World& world){
    LoadUIAssets(world);
    LoadSpriteAssets(world);
    LoadTileAssets(world);
    LoadWallpaperAssets(world);
}
