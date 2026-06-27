#include "ai_system.h"
#include <cmath>
#include <raylib.h>
#include "world_utils.h"

void UpdateAISystem(World& world, float dt){

    auto& ais = world.ais;

    for (int i = MAX_PLAYERS; i < MAX_ENTITIES; i++) {
        if (!ais.active[i]) continue; //Performance check

        //Useful data references
        auto& ai_position = world.physics.positions[i];
        auto& ai_velocities = world.physics.velocities[i];
        auto& ai_forces = world.physics.forces[i];
        auto& follow_speed = world.ais.follow_speed[i];
        auto& patrol_speed = world.ais.patrol_speed[i];


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
                ai_forces.x +=  std::sin(time) * patrol_speed;
                ai_velocities.y = 0.0f;

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
