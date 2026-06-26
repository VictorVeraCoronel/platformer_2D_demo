#include "data_loader.h"
#include "../core/world.h"
#include <cstdint>
#include <fstream>
#include <raylib.h>
#include <string>
#include "../dependencies/json.hpp"
#include <iostream>
#include "../spawners/entity_spawner.h"

// Internal auxiliar function
void ParseJsonToEntity(const nlohmann::json& json_data, Entity& entity) {
    entity.HP = json_data["hp"].get<float>();
    entity.ai_archetype = json_data["ai_archetype"].get<AIArchetype>();
    entity.jumping_force = json_data["jumping_force"].get<float>();
    entity.running_force = json_data["running_force"].get<float>();
    entity.wall_jumping_force = json_data["wall_jumping_force"].get<float>();
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
}


void LoadPlayerData(World& world){
    std::string player_path = "./game_data/players/";

    for (const auto &entry : std::filesystem::directory_iterator(player_path)) {

        // Correct file type check
        if (entry.is_regular_file() && entry.path().extension() == ".json") {

            // Safety check
            std::string file_path = entry.path().string();
            std::ifstream file(file_path);
            if (!file.is_open()) {
                std::cout << "File failed to open: " << file_path << std::endl;
                continue;
            }

            nlohmann::json json_data;
            file >> json_data;

            Entity entity;
            ParseJsonToEntity(json_data, entity);

            std::string entity_type = json_data["entity_type"];
            world.entity_repository[entity_type] = entity;

            // SUCCESS TERMINAL MESSAGE
            std::cout << "Plantilla PLAYER cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }
}

void LoadEnemiesData (World& world, std::string world_name){

    std::string enemies_path = "./game_data/enemies/" + world_name;

    for (const auto &entry : std::filesystem::directory_iterator(enemies_path)) {

        // Correct file type check
        if (entry.is_regular_file() && entry.path().extension() == ".json") {

            // Safety check
            std::string file_path = entry.path().string();
            std::ifstream file(file_path);
            if (!file.is_open()) {
                std::cout << "File failed to open: " << file_path << std::endl;
                continue;
            }

            nlohmann::json json_data;
            file >> json_data;

            Entity entity;
            ParseJsonToEntity(json_data, entity);

            std::string entity_type = json_data["entity_type"];
            world.entity_repository[entity_type] = entity;

            // SUCCESS TERMINAL MESSAGE
            std::cout << "Plantilla ENEMY cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }

}

void LoadBossesData (World& world, std::string world_name){

    std::string enemies_path = "./game_data/bosses/" + world_name;

    for (const auto &entry : std::filesystem::directory_iterator(enemies_path)) {

        // Correct file type check
        if (entry.is_regular_file() && entry.path().extension() == ".json") {

            std::string file_path = entry.path().string();
            std::ifstream file(file_path);

            // Safety check
            if (!file.is_open()) {
                std::cout << "File failed to open: " << file_path << std::endl;
                continue;
            }

            nlohmann::json json_data;
            file >> json_data;

            Entity entity;
            ParseJsonToEntity(json_data, entity);

            std::string entity_type = json_data["entity_type"];
            world.entity_repository[entity_type] = entity;

            // SUCCESS TERMINAL MESSAGE
            std::cout << "Plantilla BOSS cargada con exito: " << entry.path().filename() << " (ID: " << entity_type << ")" << std::endl;
        }
    }


}

void LoadLevelData(World &world, std::string world_name, std::string level_name){

    // Useful data references
    auto& current_level = world.current_level;
    uint16_t& width = current_level.width;
    uint16_t& height = current_level.height;
    Vector2& respawn_point = current_level.respawn_point;

    // LOAD JSON FILE
    std::string level_path = "./game_data/levels/" + world_name + "/" + level_name + ".json";
    std::ifstream level_file(level_path, std::ifstream::binary);
    nlohmann::json level_json;
    level_file >> level_json;

    // WE DO NOT WANT TO MIX LEVELS. RESET THE CURRENT ONE BEFORE LOADING THE NEW ONE.
    current_level.map.clear();

    // WE LOAD THE JSON INFORMATION INSIDE THE WORLD ATRIBUTES
    width = level_json["width"];
    height = level_json["height"];
    respawn_point = {level_json["respawn_x"].get<float>(), level_json["respawn_y"].get<float>()};

    current_level.map.resize(width * height);// This is important!
    current_level.map = level_json["map"].get<std::vector<uint8_t>>();

    // Useful data (we do this to avoid accessing the json more times than really needed)
     auto spawns = level_json["spawns"];

    // PLAYER ENTITIES SPAWN
    for(int i = 0; (i < MAX_PLAYERS && i < (int)spawns.size()); i++){
        Vector2 position = {spawns[i]["x"], spawns[i]["y"]};

        if(spawns[i]["entity_type"] == "player"){
            SpawnEntity(world, "player", position, i);
            std::cout<<"Player entity spawned!!!!"<<std::endl;
        }

    }

    // NON-PLAYER ENTITIES SPAWN
    int e_index = MAX_PLAYERS;
    for(int i = 0; i < (int)spawns.size(); i++){

        Vector2 position = {spawns[i]["x"], spawns[i]["y"]};
        std::string entity_type = spawns[i]["entity_type"];

        if(spawns[i]["entity_type"] != "player"){
           SpawnEntity(world, entity_type, position, e_index);
           e_index++;
        }


    }


}
