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

    for(int i = 0; i < MAX_PLAYERS; i++){
        if(!inputs.active[i]) continue;

        //Horizontal movement
        MoveIntentHorizontal move_intent = inputs.move_intent[i];

        switch(move_intent){

            case MoveIntentHorizontal::LEFT:{
                if(physics.is_grounded[i]){
                    physics.forces[i].x += -stats.running_force[i];
                }else{
                    physics.forces[i].x += -stats.air_movement_force[i];
                }
                break;
            }

            case MoveIntentHorizontal::RIGHT:{
                if(physics.is_grounded[i]){
                    physics.forces[i].x += stats.running_force[i];
                }else{
                    physics.forces[i].x += stats.air_movement_force[i];
                }
                break;
            }

            case MoveIntentHorizontal::NONE:{
                physics.forces[i].x += 0;
                break;
            }

        }

        //Vertical movement
        if(inputs.jump_pressed[i] && physics.is_grounded[i]){

            physics.forces[i].y -= stats.jumping_force[i];
        }


        // //Clear inputs
        // inputs.move_intent[i] = MoveIntentHorizontal::NONE;
        // inputs.jump_pressed[i] = false;
        // inputs.jump_released[i] = false;
        // inputs.run_pressed[i] = false;


        ClearInput(inputs,i);



    }


}

