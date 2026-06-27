#pragma once
#include "../core/world.h"
#include <iostream>
#include <string>
#include "../dependencies/json.hpp"

void ParseJsonToEntity(const nlohmann::json& json_data, Entity& entity);

void LoadPlayerData(World& world);

void LoadEnemiesData (World& world, std::string world_name);

void LoadBossesData (World& world, std::string world_name);

void InstantiateLevel(World &world, std::string world_name, std::string level_name);

void LoadAllData(World &world, std::string world_name, std::string level_name);
