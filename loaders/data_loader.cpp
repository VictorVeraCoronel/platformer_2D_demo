#include "../core/world.h"
#include <cstdint>
#include <fstream>
#include <string>
#include "../dependencies/json.hpp"
#include <iostream>

void LoadUIData(World& world){

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

void LoadPlayerData(World& world){

    //Load enemy path folder from string
    std::string player_path = "./game_data/players/";

    // Iteramos de forma secuencial por cada archivo de la carpeta
    for (const auto &entry : std::filesystem::directory_iterator(player_path)) {

        // Comprobamos que sea un archivo regular y que termine en .json
        if (entry.is_regular_file() && entry.path().extension() == ".json") {

            std::string file_path = entry.path().string();
            std::ifstream file(file_path);

            if (!file.is_open()) {
                //std::cout << "No se pudo abrir el archivo: " << file_path << std::endl;
                continue;
            }


            nlohmann::json json_data;
            file >> json_data;



            // 3. Extraemos los datos y los metemos en el mapa de plantillas
            // Asumimos que cada json tiene un "type_id" único dentro
            std::string entity_type = json_data["entity_type"];

            Entity entity;

            entity.HP = json_data["hp"].get<float>();
            entity.ai_archetype = json_data["ai_archetype"].get<AIArchetype>();
            entity.jumping_force = json_data["jumping_force"].get<float>();
            entity.running_force = json_data["running_force"].get<float>();
            entity.air_movement_force = json_data["air_movement_force"].get<float>();
            entity.n_animation_frames = json_data["n_animation_frames"].get<uint8_t>();
            entity.anim_speed = json_data["anim_speed"].get<float>();
            entity.sprite_height = json_data["sprite_height"].get<uint16_t>();
            entity.sprite_width = json_data["sprite_width"].get<uint16_t>();
            entity.sprite_id = json_data["sprite_id"].get<uint16_t>();
            entity.width = json_data["width"].get<uint16_t>();
            entity.height = json_data["width"].get<uint16_t>();


            // Insertamos en el contenedor del World
            world.entity_repository[entity_type] = entity;

            std::cout << "Plantilla cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }
}

void LoadEnemiesData (World& world, std::string dungeon_name){
    //Load enemy path folder from string
    std::string path_1 = "./game_data/enemies/";
    std::string path_2 = dungeon_name;
    std::string enemies_path = path_1 + path_2;

    // Iteramos de forma secuencial por cada archivo de la carpeta
    for (const auto &entry : std::filesystem::directory_iterator(enemies_path)) {

        // Comprobamos que sea un archivo regular y que termine en .json
        if (entry.is_regular_file() && entry.path().extension() == ".json") {

            std::string file_path = entry.path().string();
            std::ifstream file(file_path);

            if (!file.is_open()) {
                //std::cout << "No se pudo abrir el archivo: " << file_path << std::endl;
                continue;
            }



            nlohmann::json json_data;
            file >> json_data;



            // 3. Extraemos los datos y los metemos en el mapa de plantillas
            // Asumimos que cada json tiene un "type_id" único dentro
            std::string entity_type = json_data["entity_type"];

            Entity entity;

            entity.HP = json_data["hp"].get<float>();
            entity.ai_archetype = json_data["ai_archetype"].get<AIArchetype>();
            entity.jumping_force = json_data["jumping_force"].get<float>();
            entity.running_force = json_data["running_force"].get<float>();
            entity.air_movement_force = json_data["air_movement_force"].get<float>();
            entity.n_animation_frames = json_data["n_animation_frames"].get<uint8_t>();
            entity.anim_speed = json_data["anim_speed"].get<float>();
            entity.sprite_height = json_data["sprite_height"].get<uint16_t>();
            entity.sprite_width = json_data["sprite_width"].get<uint16_t>();
            entity.sprite_id = json_data["sprite_id"].get<uint16_t>();
            entity.width = json_data["width"].get<uint16_t>();
            entity.height = json_data["width"].get<uint16_t>();

            // Insertamos en el contenedor del World
            world.entity_repository[entity_type] = entity;

            std::cout << "Plantilla cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }

}

void LoadBossesData (World& world, std::string dungeon_name){

    //Load enemy path folder from string
    std::string path_1 = "./game_data/bosses/";
    std::string path_2 = dungeon_name;
    std::string enemies_path = path_1 + path_2;

    // Iteramos de forma secuencial por cada archivo de la carpeta
    for (const auto &entry : std::filesystem::directory_iterator(enemies_path)) {

        // Comprobamos que sea un archivo regular y que termine en .json
        if (entry.is_regular_file() && entry.path().extension() == ".json") {

            std::string file_path = entry.path().string();
            std::ifstream file(file_path);

            if (!file.is_open()) {
                //std::cout << "No se pudo abrir el archivo: " << file_path << std::endl;
                continue;
            }



            nlohmann::json json_data;
            file >> json_data;



            // 3. Extraemos los datos y los metemos en el mapa de plantillas
            // Asumimos que cada json tiene un "type_id" único dentro
            std::string entity_type = json_data["entity_type"];

            Entity entity;

            entity.HP = json_data["hp"].get<float>();
            entity.ai_archetype = json_data["ai_archetype"].get<AIArchetype>();
            entity.jumping_force = json_data["jumping_force"].get<float>();
            entity.running_force = json_data["running_force"].get<float>();
            entity.air_movement_force = json_data["air_movement_force"].get<float>();
            entity.n_animation_frames = json_data["n_animation_frames"].get<uint8_t>();
            entity.anim_speed = json_data["anim_speed"].get<float>();
            entity.sprite_height = json_data["sprite_height"].get<uint16_t>();
            entity.sprite_width = json_data["sprite_width"].get<uint16_t>();
            entity.sprite_id = json_data["sprite_id"].get<uint16_t>();
            entity.width = json_data["width"].get<uint16_t>();
            entity.height = json_data["width"].get<uint16_t>();

            // Insertamos en el contenedor del World
            world.entity_repository[entity_type] = entity;

            std::cout << "Plantilla cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }


}
