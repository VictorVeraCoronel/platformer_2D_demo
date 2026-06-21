#include "../core/world.h"
#include <fstream>
#include <string>
#include "../dependencies/json.hpp"

void LoadUIAssets(World& world){

    auto& asset_repository = world.asset_repository;

    //Load sprites path folder from string
    std::string sprites_path = "./game_data/textures/ui.json";
    std::ifstream sprites_file(sprites_path, std::ifstream::binary);

    std::map<int , std::string> ui_map;

    if (sprites_file.is_open()) {

        nlohmann::json sprites_json;
        sprites_file >> sprites_json;

        // Iteramos por cada elemento del array "sprites_assets"
        for (const auto& item : sprites_json["ui_assets"]) {
            // Cada 'item' es un objeto, por ejemplo: {"0" : "ruta.png"}
            // Lo iteramos para obtener su clave (key) y su valor (value)
            for (auto it = item.begin(); it != item.end(); ++it) {
                int id = std::stoi(it.key()); // Convertimos el string "0" a int 0
                std::string path = it.value();

                ui_map[id] = path; // Lo guardamos en nuestro mapa
            }
        }
    }



    for(int i = 0; i < ui_map.size(); i++){
        //std::cout<<sprites_map[i]<<std::endl;
        asset_repository.ui[i] = LoadTexture(ui_map[i].c_str());
    }
}

void LoadSpriteAssets(World &world){

    auto& asset_repository = world.asset_repository;

    //Load sprites path folder from string
    std::string sprites_path = "./game_data/textures/sprites.json";

    std::ifstream sprites_file(sprites_path, std::ifstream::binary);

    std::map<int , std::string> sprites_map;

    if (sprites_file.is_open()) {

        nlohmann::json sprites_json;
        sprites_file >> sprites_json;

        // Iteramos por cada elemento del array "sprites_assets"
        for (const auto& item : sprites_json["sprites_assets"]) {
            // Cada 'item' es un objeto, por ejemplo: {"0" : "ruta.png"}
            // Lo iteramos para obtener su clave (key) y su valor (value)
            for (auto it = item.begin(); it != item.end(); ++it) {
                int id = std::stoi(it.key()); // Convertimos el string "0" a int 0
                std::string path = it.value();

                sprites_map[id] = path; // Lo guardamos en nuestro mapa
            }
        }
    }



    for(int i = 0; i < sprites_map.size(); i++){
        //std::cout<<sprites_map[i]<<std::endl;
        asset_repository.sprite[i] = LoadTexture(sprites_map[i].c_str());
    }

}


void LoadTileAssets(World &world){
    auto& asset_repository = world.asset_repository;

    //Load tiles path folder from string
    std::string tiles_path = "./game_data/textures/tiles.json";

    std::ifstream tiles_file(tiles_path, std::ifstream::binary);

    std::map<int , std::string> tiles_map;

    if (tiles_file.is_open()) {

        nlohmann::json tiles_json;
        tiles_file >> tiles_json;

        // Iteramos por cada elemento del array "sprites_assets"
        for (const auto& item : tiles_json["tiles_assets"]) {
            // Cada 'item' es un objeto, por ejemplo: {"0" : "ruta.png"}
            // Lo iteramos para obtener su clave (key) y su valor (value)
            for (auto it = item.begin(); it != item.end(); ++it) {
                int id = std::stoi(it.key()); // Convertimos el string "0" a int 0
                std::string path = it.value();

                tiles_map[id] = path; // Lo guardamos en nuestro mapa
            }
        }
    }



    for(int i = 0; i < tiles_map.size(); i++){
        //std::cout<<tiles_map[i]<<std::endl;
       asset_repository.tile[i] = LoadTexture(tiles_map[i].c_str());
    }

}
