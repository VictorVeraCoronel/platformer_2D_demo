#pragma once
#include "../core/world.h"
#include <iostream>
#include <string>

void LoadPlayerData(World& world);

void LoadEnemiesData (World& world, std::string dungeon_name);

void LoadBossesData (World& world, std::string dungeon_name);

void LoadLevelData(World &world, std::string world_name, std::string level_name);
