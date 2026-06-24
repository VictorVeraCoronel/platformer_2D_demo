#include "../../core/world.h"
#include <iostream>

void UpdatePhysics(World& world, float dt){

    //Global useful data references
    auto& physics = world.physics;
    auto& level = world.current_level;
    const float gravity = world.gravity;
    const float fall_multiplier = world.fall_gravity_multiplier;


    for(int i = 0; i < MAX_ENTITIES; i++){
        //Performance filter
        if (!physics.active[i]) continue;

        //Current entity useful data references
        bool& has_desired_position = physics.has_desired_position[i];
        float& desired_pos_x = physics.desired_positions[i].x;
        float& desired_pos_y = physics.desired_positions[i].y;
        float& pos_x = physics.positions[i].x;
        float& pos_y = physics.positions[i].y;
        float& vel_x = physics.velocities[i].x;
        float& vel_y = physics.velocities[i].y;
        float& forces_x = physics.forces[i].x;
        float& forces_y = physics.forces[i].y;
        float& size_x = physics.sizes[i].x;
        float& size_y = physics.sizes[i].y;
        bool& is_grounded = physics.is_grounded[i];

        float entity_mass = (physics.mass[i] > 0.0f) ? physics.mass[i] : 1.0f;
        float current_gravity =(physics.velocities[i].y > 0.0f) ? gravity * fall_multiplier : gravity;

        if(!has_desired_position){
            pos_x = desired_pos_x;
            pos_y = desired_pos_y;
            has_desired_position = true;
        }

        //We apply gravity force
        forces_y += (entity_mass * current_gravity);

        //We sum forces to velocities
        vel_x += (forces_x / entity_mass) * dt;
        vel_y += (forces_y / entity_mass) * dt;

        //Clear forces
        forces_x = 0;
        forces_y = 0;


        // ---------------
        // X axis collision - START
        // ---------------

        float next_pos_x = pos_x + (vel_x*dt);
        bool collision_x = false;


        if(vel_x > 0){//If player wants to move right
            uint16_t index_top = level.GetTileIndexAtPosition((next_pos_x + size_x -1), pos_y);
            uint16_t index_bottom = level.GetTileIndexAtPosition((next_pos_x + size_x -1), (pos_y + size_y -1));

            if (level.map[index_top] > 0 || level.map[index_bottom] > 0) collision_x = true;
        }

        if(vel_x < 0){//If player wants to move right
            uint16_t index_top =  level.GetTileIndexAtPosition(next_pos_x, pos_y);
            uint16_t index_bottom = level.GetTileIndexAtPosition(next_pos_x, (pos_y + size_y -1));

            if (level.map[index_top] > 0 || level.map[index_bottom] > 0) collision_x = true;
        }

        if (collision_x) {
            vel_x = 0.0f;
        } else {
            pos_x = next_pos_x;
        }

        // ---------------
        // X axis collision - FINISH
        // ---------------



        // ---------------
        // Y axis collision
        // ---------------

        float next_pos_y = pos_y + (vel_y*dt);
        bool collision_y = false;


        if (vel_y > 0) {
            int index_left = level.GetTileIndexAtPosition(pos_x, (next_pos_y + size_y));
            int index_right = level.GetTileIndexAtPosition((pos_x + size_x - 1),(next_pos_y + size_y));

            if (level.map[index_left] > 0 || level.map[index_right] > 0){
                int tile_row = (int)((next_pos_y + size_y) / TILE_SIZE);
                pos_y = (tile_row * TILE_SIZE) - size_y;


                collision_y = true;
                is_grounded = true;
            }
        }
        else if (vel_y < 0) {
            int index_left  = level.GetTileIndexAtPosition(pos_x , next_pos_y);
            int index_right =  level.GetTileIndexAtPosition((pos_x + size_x - 1), (next_pos_y / TILE_SIZE));

            if (level.map[index_left] > 0 || level.map[index_right] > 0) collision_y = true;
        }

        if (collision_y) {
            vel_y = 0.0f;
        } else {
            pos_y = next_pos_y;
            if (vel_y > 0.1f) is_grounded = false;
        }

        // ---------------
        // Y axis collision
        // ---------------



        //Apply frictions with ground and air
        if(is_grounded){
            vel_x *=  GROUND_FRICTION;
        }else{
            vel_x *=  AIR_FRICTION;
        }




    }
}
