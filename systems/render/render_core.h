#pragma once
#include "../../core/world.h"

struct RenderScreenContext {
    RenderTexture2D virtual_target;
    float virtual_width;
    float virtual_height;
};

void RenderCore(const World& world, Camera2D& camera, const VirtualScreen& virtual_screen);

VirtualScreen LoadVirtualScreen(int v_screen_width, int v_screen_height, int texture_width, int texture_height);

