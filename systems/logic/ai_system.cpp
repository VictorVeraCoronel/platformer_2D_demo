#include "ai_system.h"
#include <cmath>
#include <raylib.h>
#include "world_utils.h"
#include <iostream>

void UpdateAISystem(World& world){

    auto& ais = world.ais;

    for (int i = MAX_PLAYERS; i < MAX_ENTITIES; i++) {
        if (!ais.active[i]) continue; //Performance check

        //Useful data references
        const auto& ai_size = world.physics.sizes[i];
        auto& ai_position = world.physics.positions[i];
        auto& ai_velocities = world.physics.velocities[i];
        auto& ai_forces = world.physics.forces[i];
        auto& follow_speed = world.ais.follow_speed[i];
        auto& patrol_speed = world.ais.patrol_speed[i];
        const auto& level = world.current_level;


        // LOOK FOR NEAREST PLAYER TO ENTITY
        int16_t nearest_player = GetClosestPlayerIndex(world, ai_position);

        // IF THERE ARE NO PLAYERS, AI WILL NOT UPDATE
        if (nearest_player == -1) continue;

        Vector2 closest_player_position = world.physics.positions[nearest_player];

        switch (ais.ai_states[i]) {

            case AIState::IDLE:{
                ai_velocities = {0.0f, 0.0f};

                break;
            }

            case AIState::PATROL:{

                float time = GetTime();
                int8_t force_sign = 1;

                if(std::sin(time) > 0){
                    force_sign = 1;
                }else{
                    force_sign = -1;
                }

                float horizontal_force = force_sign * patrol_speed;

                Vector2 next_position;

                if(force_sign == 1)  next_position = {ai_position.x + (ai_size.x*2) , ai_position.y + ai_size.y};
                if(force_sign == -1) next_position = {ai_position.x - (ai_size.x*1) , ai_position.y + ai_size.y};


                int index = level.GetTileIndexAtPosition(next_position.x, next_position.y);
                if(level.map[index] != 0){
                    ai_forces.x += horizontal_force;
                    ai_velocities.y = 0.0f;
                }else{
                    ai_velocities = {0,0};
                }


                break;
            }

            case AIState::FOLLOW:{

                Vector2 to_player = {closest_player_position.x - ai_position.x, closest_player_position.y - ai_position.y};
                float distance = std::sqrt((to_player.x * to_player.x) + (to_player.y * to_player.y));

                if(distance > 0.1f){
                    ai_forces.x += (to_player.x / distance) * follow_speed;
                }

                break;
            }

        }


    }






}
