#include "world_utils.h"

uint16_t GetClosestPlayerIndex(const World& world, Vector2 entity_position) {
    float min_distance_squared = 99999999.0f;
    int closest_player_index = -1;

    for (int p = 0; p < MAX_PLAYERS; p++) {
        if (!world.inputs.active[p]) continue; // Solo jugadores activos

        const auto& player_position = world.physics.positions[p];

        float dx = player_position.x - entity_position.x;
        float dy = player_position.y - entity_position.y;
        float dist_sq = (dx * dx) + (dy * dy);

        if (dist_sq < min_distance_squared) {
            min_distance_squared = dist_sq;
            closest_player_index = p;
        }
    }

    return closest_player_index;
}

void KillEntity(World& world, int i){

    if( i >= MAX_PLAYERS){
        world.stats.active[i] = false;
        world.physics.active[i] = false;
        world.sounds.active[i] = false;
        world.ais.active[i] = false;
        world.animations.active[i] = false;
        world.locomotions.active[i] = false;
        world.renders.active[i] = false;
        std::cout<<"Sa muerto"<<std::endl;
    }else{

    }


}
