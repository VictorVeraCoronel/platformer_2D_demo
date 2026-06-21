#include "../../core/world.h"
#include <raylib.h>

void RenderCore(World& world){
    auto& renders = world.renders;
    auto& physics = world.physics;

    for(int i =0; i < MAX_ENTITIES; i++){
        if(!renders.active[i]) continue;

        Rectangle rectangle = {physics.positions[i].x, physics.positions[i].y, 128 ,256};
        DrawRectangleRec(rectangle, RED);

    }


}
