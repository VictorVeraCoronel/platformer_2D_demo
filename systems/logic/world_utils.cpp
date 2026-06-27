#include "world_utils.h"

int16_t GetClosestPlayerIndex(const World& world, Vector2 entity_position) {
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
