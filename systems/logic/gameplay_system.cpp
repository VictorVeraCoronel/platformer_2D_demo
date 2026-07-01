#include "gameplay_system.h"
#include "world_utils.h" //Do not remove, it is commented right now but will be used
#include <iostream>

void UpdateGameplay(World& world, float dt){

    for(int i = 0; i < MAX_ENTITIES; i++){
        world.stats.inmune_timer[i] -= dt;
    }

    // GENERAL GAMEPLAY UPDATES
    ApplyPendingDamage(world, dt);

    // PLAYERS GAMEPLAY UPDATES
    OrderPhysicsFromInput(world);
    UpdateAnimationState(world);
    ResetOutOfBounds(world);
    ResetIfDead(world);
    ClearInput(world);

    // ENTITIES GAMEPLAY UPDATES
    UpdateEntityBehaviour(world);
    UpdateEntityAnimations(world);



}

// GENERAL GAMEPLAY FUNCTIONS
void ApplyPendingDamage(World& world, float dt){
    auto& stats = world.stats;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(!stats.active[i]) continue;

        auto& hp = stats.hp[i];
        auto& pending_damage = stats.pending_damage[i];
        auto& inmune_timer = stats.inmune_timer[i];
        bool invulnerable = inmune_timer > 0.0f;

        if(pending_damage <= 0) continue;

        if(invulnerable){
            pending_damage = 0;
        }else{
            hp -= pending_damage;
            pending_damage = 0;
            inmune_timer = 1.0f;
        }

        if(hp <= 0){
            KillEntity(world, i);
        }
    }
}


// PLAYERS GAMEPLAY FUNCTIONS

void OrderPhysicsFromInput(World& world){
    auto& inputs = world.inputs;
    auto& physics = world.physics;
    auto& locomotions = world.locomotions;

    for(int i = 0; i < MAX_PLAYERS; i++){
        if(!inputs.active[i]) continue;

        // Useful data references
        MoveIntentHorizontal& move_intent = inputs.move_intent[i];
        bool& jump_pressed = inputs.jump_pressed[i];
        bool& jump_released = inputs.jump_released[i];
        float& forces_x = physics.forces[i].x;
        float& velocity_x = physics.velocities[i].x;
        float& velocity_y = physics.velocities[i].y;
        float& coyote_timer = physics.coyote_timer[i];
        WallCollision& wall_collision = physics.wall_collision[i];
        bool& is_grounded = physics.is_grounded[i];
        float& running_force = locomotions.running_force[i];
        float& jumping_force = locomotions.jumping_force[i];
        float& wall_jumping_force = locomotions.wall_jumping_force[i];
        float& air_movement_force = locomotions.air_movement_force[i];

        //HORIZONTAL MOVEMENT
        switch(move_intent){

            case MoveIntentHorizontal::LEFT:{
                if(is_grounded){
                    forces_x -= running_force;
                }else{
                    forces_x -= air_movement_force;
                }
                break;
            }

            case MoveIntentHorizontal::RIGHT:{
                if(is_grounded){
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

        // VERTICAL MOVEMENT (JUMP)
        if(jump_pressed && coyote_timer > 0.01f && wall_collision == WallCollision::NONE){
            velocity_y = -jumping_force;
            is_grounded = false;
            coyote_timer = 0.0f;
        }

        // VARIABLE JUMP BEHAVIOUR
        if(jump_released && velocity_y < 0){
            velocity_y *= 0.6f;
        }

        // WALL JUMP FROM LEFT
        if(jump_pressed && wall_collision == WallCollision::LEFT && velocity_y > 0){
            velocity_y = -jumping_force;
            velocity_x = wall_jumping_force;
            is_grounded = false;
            coyote_timer = 0.0f;
            inputs.horizontal_lock_timer[i] = 0.4f;
            wall_collision = WallCollision::NONE;
        }

        // WALL JUMP FROM RIGHT
        if(jump_pressed && wall_collision == WallCollision::RIGHT && velocity_y > 0){
            velocity_y = -jumping_force;
            velocity_x = -wall_jumping_force;
            is_grounded = false;
            coyote_timer = 0.0f;
            inputs.horizontal_lock_timer[i] = 0.4f;
            wall_collision = WallCollision::NONE;
        }

    }
}

void UpdateAnimationState(World& world){
    auto& physics = world.physics;
    auto& animations = world.animations;
    auto& inputs = world.inputs;

    for(int i = 0; i < MAX_PLAYERS; i++){
        if(!inputs.active[i]) continue;

        animations.state[i] = AnimState::IDLE;

        //GROUND ANIMATIONS
        if(physics.is_grounded[i]){
            if (std::abs(physics.velocities[i].x) > 40.0f) {
                animations.state[i] = AnimState::RUNNING;
            }
        }

        //WALL ANIMATIONS
        else if(physics.wall_collision[i] != WallCollision::NONE){
            animations.state[i] = AnimState::WALL_SLIDING;
        }

        //MID AIR ANIMATIONS
        else if (!physics.is_grounded[i]) {
            if (physics.velocities[i].y < 0.0f) {
                animations.state[i] = AnimState::JUMPING;
            } else {
                animations.state[i] = AnimState::FALLING;
            }
        }


    }

}

void ResetOutOfBounds(World& world){
    auto& physics = world.physics;
    auto& level = world.current_level;

    for(int i = 0; i < MAX_PLAYERS; i++){
        if(!physics.active[i]) continue;

        //Level reset if out of bounds.
        float& vel_y = physics.velocities[i].y;
        float& pos_y = physics.positions[i].y;
        float& desired_pos_x = physics.desired_positions[i].x;
        float& desired_pos_y = physics.desired_positions[i].y;
        bool& has_desired_position = physics.has_desired_position[i];

        if(pos_y > level.height*TILE_SIZE){
            vel_y = 0; // We reset Y axis velocity to avoid entering walls
            desired_pos_x = level.respawn_point.x;
            desired_pos_y = level.respawn_point.y;
            has_desired_position = true;

        }

    }
}

void ResetIfDead(World& world){
    auto& physics = world.physics;
    auto& stats = world.stats;
    auto& level = world.current_level;

    for(int i = 0; i < MAX_PLAYERS; i++){
        if(!stats.active[i]) continue;
        auto& player_hp = stats.hp[i];
        float& vel_y = physics.velocities[i].y;
        float& pos_y = physics.positions[i].y;
        float& desired_pos_x = physics.desired_positions[i].x;
        float& desired_pos_y = physics.desired_positions[i].y;
        bool& has_desired_position = physics.has_desired_position[i];

        if(player_hp <= 0){
            vel_y = 0; // We reset Y axis velocity to avoid entering walls
            desired_pos_x = level.respawn_point.x;
            desired_pos_y = level.respawn_point.y;
            has_desired_position = true;
            player_hp = stats.max_hp[i];
        }

    }

}

void ClearInput(World& world){
    auto& inputs = world.inputs;
    auto &physics = world.physics;

    for(int i = 0; i < MAX_PLAYERS; i++){
        if(!inputs.active[i]) continue;

        inputs.move_intent[i] = MoveIntentHorizontal::NONE;
        inputs.jump_pressed[i] = false;
        inputs.jump_released[i] = false;
        inputs.run_pressed[i] = false;

        //Clear wall collisions
        physics.wall_collision[i] = WallCollision::NONE;
    }


}


// ENTITIES GAMEPLAY FUNCTIONS
void UpdateEntityBehaviour(World& world){
    auto& ais = world.ais;

    for(int i = MAX_PLAYERS; i < MAX_ENTITIES; i++){
        if(!ais.active[i]) continue;


        // Useful data references
        // const auto& e_position = world.physics.positions[i];
        //uint_16_t player_index = GetClosestPlayerIndex(world, e_position);
        // const auto& p_position = world.physics.positions[player_index];
        // const auto& aggro_range = world.ais.aggro_range[i];
        auto& ai_state = world.ais.ai_states[i];
        //
        // // DISTANCE BETWEEN ENTITY AND PLAYER;
        // Vector2 e_p_vector = {(e_position.x - p_position.x) , (e_position.y - p_position.y)};

        // CALCULATION OF SQUARE OF DISTANCE AND AGGRO RANGE TO AVOID USING SQUARE ROOT, AS IT PRODUCES LATENCY.
        // float distance_squared = (e_p_vector.x * e_p_vector.x) + (e_p_vector.y * e_p_vector.y);
        // float aggro_range_squared = aggro_range * aggro_range;


        // IF THE ENEMY GETS NEAR ENOUGH, IT WILL FOLLOW THE PLAYER
        // if (distance_squared <= aggro_range_squared){
        //     ai_state = AIState::FOLLOW;
        // }

        // IF THE PLAYER IS FAR AWAY, THE ENEMY PATROLS
        // else{
        //     ai_state = AIState::PATROL;
        // }

        ai_state = AIState::PATROL;
    }

}

void UpdateEntityAnimations(World& world){
    auto& physics = world.physics;
    auto& animations = world.animations;
    auto& ais = world.ais;

    for(int i = MAX_PLAYERS; i < MAX_ENTITIES; i++){
        if(!ais.active[i]) continue;

        animations.state[i] = AnimState::IDLE;

        //GROUND ANIMATIONS
        if(physics.is_grounded[i]){
            if (std::abs(physics.velocities[i].x) > 40.0f) {
                animations.state[i] = AnimState::RUNNING;
            }
        }

        //WALL ANIMATIONS
        else if(physics.wall_collision[i] != WallCollision::NONE){
            animations.state[i] = AnimState::WALL_SLIDING;
        }

        //MID AIR ANIMATIONS
        else if (!physics.is_grounded[i]) {
            if (physics.velocities[i].y < 0.0f) {
                animations.state[i] = AnimState::JUMPING;
            } else {
                animations.state[i] = AnimState::FALLING;
            }
        }



    }


}




