#pragma once
#include "../core/world.h"
#include <iostream>
#include <string>

void LoadUIData(World& world);

void LoadPlayerData(World& world);

void LoadEnemiesData (World& world, std::string dungeon_name);

void LoadBossesData (World& world, std::string dungeon_name);
