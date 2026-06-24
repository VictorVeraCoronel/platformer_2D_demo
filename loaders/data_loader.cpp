#include "data_loader.h"
#include "../core/world.h"
#include <cstdint>
#include <fstream>
#include <raylib.h>
#include <string>
#include "../dependencies/json.hpp"
#include <iostream>
#include "../spawners/entity_spawner.h"



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
            entity.height = json_data["height"].get<uint16_t>();
            entity.mass = json_data["mass"].get<float>();
            entity.aggro_range = json_data["aggro_range"].get<float>();


            // Insertamos en el contenedor del World
            world.entity_repository[entity_type] = entity;

            std::cout << "Plantilla cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }
}

void LoadEnemiesData (World& world, std::string world_name){
    //Load enemy path folder from string
    std::string path_1 = "./game_data/enemies/";
    std::string path_2 = world_name;
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
            entity.height = json_data["height"].get<uint16_t>();
            entity.mass = json_data["mass"].get<float>();
            entity.aggro_range = json_data["aggro_range"].get<float>();

            // Insertamos en el contenedor del World
            world.entity_repository[entity_type] = entity;

            std::cout << "Plantilla cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }

}

void LoadBossesData (World& world, std::string world_name){

    //Load enemy path folder from string
    std::string path_1 = "./game_data/bosses/";
    std::string path_2 = world_name;
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
            entity.height = json_data["height"].get<uint16_t>();

            // Insertamos en el contenedor del World
            world.entity_repository[entity_type] = entity;

            std::cout << "Plantilla cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }


}

void LoadLevelData(World &world, std::string world_name, std::string level_name){

    //Load json file
    std::string level_path = "./game_data/levels/" + world_name + "/" + level_name + ".json";
    std::ifstream level_file(level_path, std::ifstream::binary);
    nlohmann::json level_json;
    level_file >> level_json;


    auto& current_level = world.current_level;
    uint16_t& width = current_level.width;
    uint16_t& height = current_level.height;
    Vector2& respawn_point = current_level.respawn_point;

    //We clear the dungeon in case of duplicating this line of code somewhere.
    current_level.map.clear();

    //Extracting data from json into variables
    width = level_json["width"];
    height = level_json["height"];
    respawn_point = {level_json["respawn_x"].get<float>(), level_json["respawn_y"].get<float>()};


    //Load dungeon data in array dungeon
    current_level.map.resize(width * height);
    current_level.map = level_json["map"].get<std::vector<uint8_t>>();

    //Spawn all entities
     auto spawns = level_json["spawns"];



    //First, we spawn the players
    for(int i = 0; (i < MAX_PLAYERS && i < spawns.size()); i++){
        Vector2 position = {spawns[i]["x"], spawns[i]["y"]};

        if(spawns[i]["entity_type"] == "player"){
            SpawnEntity(world, "player", position, i);
            std::cout<<"Player entity spawned!!!!"<<std::endl;
        }

    }

    //Now, we spawn the rest of the entities
    for(int i = 0; i < spawns.size(); i++){
        int initial_enemy_index = MAX_PLAYERS;

        Vector2 position = {spawns[i]["x"], spawns[i]["y"]};
        std::string entity_type = spawns[i]["entity_type"];

        if(spawns[i]["entity_type"] != "player"){
           SpawnEntity(world, entity_type, position, initial_enemy_index);
        }

        initial_enemy_index++;
    }


}
