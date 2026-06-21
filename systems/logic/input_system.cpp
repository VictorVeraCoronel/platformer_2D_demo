#include "../../core/world.h"
#include <raylib.h>

void ClearInput(InputComponent& inputs,int i){
    inputs.move_intent[i] = MoveIntentHorizontal::NONE;
    inputs.jump_pressed[i] = false;
    inputs.jump_released[i] = false;
    inputs.run_pressed[i] = false;
}

void UpdateInput(World& world){

    auto& inputs = world.inputs;

    for(int i = 0; i < MAX_PLAYERS; i++){
        if (!inputs.active[i]) continue;//Performance check

        ClearInput(inputs, i);

        int PLAYER = i;
        switch (PLAYER){

            case 0:{
                //HORIZONTAL
                if(IsKeyDown(KEY_D)) inputs.move_intent[i] = MoveIntentHorizontal::RIGHT;
                if(IsKeyDown(KEY_A)) inputs.move_intent[i] = MoveIntentHorizontal::LEFT;

                //JUMPING
                if(IsKeyPressed(KEY_SPACE)) inputs.jump_pressed[i] = true;
                if(IsKeyReleased(KEY_SPACE)) inputs.jump_released[i] = true;

                //SPRINT
                if(IsKeyDown(KEY_LEFT_SHIFT)) inputs.run_pressed[i] = true;

                break;
            }

            case 1:{
                break;
            }

            case 2:{
                break;
            }

            case 3:{
                break;
            }


        }


    }
}


