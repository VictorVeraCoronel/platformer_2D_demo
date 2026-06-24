#include "../../core/world.h"
#include <iostream>

void ClearInput(InputComponent& inputs,int i){
    inputs.move_intent[i] = MoveIntentHorizontal::NONE;
    inputs.jump_pressed[i] = false;
    inputs.jump_released[i] = false;
    inputs.run_pressed[i] = false;
}

void UpdateGameplay(World& world){

    //PLAYER NATURAL INTELLIGENCE
    auto& stats = world.stats;
    auto& inputs = world.inputs;
    auto& physics = world.physics;
    auto& gravity = world.gravity;
    auto& level = world.current_level;

    for(int i = 0; i < MAX_PLAYERS; i++){
        if(!inputs.active[i]) continue;

        // Useful data references
        MoveIntentHorizontal move_intent = inputs.move_intent[i];
        float& forces_x = physics.forces[i].x;
        float& forces_y = physics.forces[i].y;
        float& running_force = stats.running_force[i];
        float& jumping_force = stats.jumping_force[i];
        float& air_movement_force = stats.air_movement_force[i];



        switch(move_intent){

            case MoveIntentHorizontal::LEFT:{
                if(physics.is_grounded[i]){
                    forces_x -= running_force;
                }else{
                    forces_x -= air_movement_force;
                }
                break;
            }

            case MoveIntentHorizontal::RIGHT:{
                if(physics.is_grounded[i]){
                    forces_x += running_force;
                }else{
                    forces_x += air_movement_force;
                }
                break;
            }

            case MoveIntentHorizontal::NONE:{

                break;
            }

        }

        //Vertical movement
        if(inputs.jump_pressed[i] && physics.is_grounded[i]){

            forces_y -= jumping_force;
        }

        ClearInput(inputs,i);



        float& pos_x = physics.positions[i].x;
        float& pos_y = physics.positions[i].y;
        float& desired_pos_x = physics.desired_positions[i].x;
        float& desired_pos_y = physics.desired_positions[i].y;
        bool& has_desired_position = physics.has_desired_position[i];

        if(pos_y > level.height*TILE_SIZE || pos_x > level.width*TILE_SIZE || pos_x < 0){
            desired_pos_x = level.respawn_point.x;
            desired_pos_y = level.respawn_point.y;
            has_desired_position = false;
        }

    }


}

