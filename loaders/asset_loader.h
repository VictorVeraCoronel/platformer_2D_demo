#pragma once
#include "../core/world.h"
#include <iostream>
#include <string>

void LoadTextureCategory(Texture2D* target_array, const std::string& json_path, const std::string& asset_key);

void LoadUIAssets(World& world);

void LoadSpriteAssets(World &world);

void LoadTileAssets(World &world);

void LoadWallpaperAssets(World &world);
