#pragma once
#include "../../core/world.h"
#include "raylib.h"


//Function that controls how the camera follows the player.
void FollowCamera(World &world, Camera2D &camera, float dt);

void InitCameraManager(World &world, Camera2D &camera);
