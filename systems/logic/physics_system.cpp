#include "../../core/world.h"
#include <iostream>


void IntegrateForces(World& world, float dt, uint16_t i){
    auto& physics = world.physics;

    const float gravity = world.gravity;
    const float fall_multiplier = world.fall_gravity_multiplier;
    float current_gravity =(physics.velocities[i].y > 0.0f) ? gravity * fall_multiplier : gravity;

    //Useful data references
    bool& has_desired_position = physics.has_desired_position[i];
    float& desired_pos_x = physics.desired_positions[i].x;
    float& desired_pos_y = physics.desired_positions[i].y;
    float& pos_x = physics.positions[i].x;
    float& pos_y = physics.positions[i].y;

    float& forces_x = physics.forces[i].x;
    float& forces_y = physics.forces[i].y;
    float& vel_x = physics.velocities[i].x;
    float& vel_y = physics.velocities[i].y;
    float entity_mass = (physics.mass[i] > 0.0f) ? physics.mass[i] : 1.0f;

    // UPDATE POSITION AS REQUESTED BY GAMEPLAY SYSTEM
    if(!has_desired_position){
        pos_x = desired_pos_x;
        pos_y = desired_pos_y;
        has_desired_position = true;
    }

    // APPLY GRAVITY FORCE
    forces_y += (entity_mass * current_gravity);

    // WE SUM THE FORCES OBTAINED FROM GAMEPLAY SYSTEM
    vel_x += (forces_x / entity_mass) * dt;
    vel_y += (forces_y / entity_mass) * dt;

    // CLEAR ALL FORCES
    forces_x = 0;
    forces_y = 0;

};

void ResolveXCollisions(World& world, float dt, uint16_t i){
    auto& physics = world.physics;
    auto& level = world.current_level;

    // Useful data references
    float& pos_x = physics.positions[i].x;
    float& pos_y = physics.positions[i].y;
    float& vel_x = physics.velocities[i].x;
    float& vel_y = physics.velocities[i].y;
    float& size_x = physics.sizes[i].x;
    float& size_y = physics.sizes[i].y;
    bool& is_grounded = physics.is_grounded[i];


    // Collision data
    float next_pos_x = pos_x + (vel_x*dt);
    bool collision_x = false;
    WallCollision wall_collision = WallCollision::NONE;

    //CHECK COLLISIONS WHEN MOVING RIGHT
    if(vel_x > 0){
        uint16_t index_top = level.GetTileIndexAtPosition((next_pos_x + size_x -1), pos_y);
        uint16_t index_bottom = level.GetTileIndexAtPosition((next_pos_x + size_x -1), (pos_y + size_y -1));

        if (level.map[index_top] > 0 || level.map[index_bottom] > 0){
            collision_x = true;
            wall_collision = WallCollision::RIGHT;
        }
    }

    // CHECK COLLISIONS WHEN MOVING LEFT
    if(vel_x < 0){
        uint16_t index_top =  level.GetTileIndexAtPosition(next_pos_x, pos_y);
        uint16_t index_bottom = level.GetTileIndexAtPosition(next_pos_x, (pos_y + size_y -1));

        if (level.map[index_top] > 0 || level.map[index_bottom] > 0){
            collision_x = true;
            wall_collision = WallCollision::LEFT;
        }
    }

    // RESOLVE BEHAVIOUR DEPENDING ON RESULTS
    if (collision_x) {
        vel_x = 0.0f;// Halt X movement

        if (!is_grounded && vel_y > 0.0f) {
            physics.wall_collision[i] = wall_collision;
        }else{
            physics.wall_collision[i] = WallCollision::NONE;
        }

    }
    else {
        // Just move
        pos_x = next_pos_x;
        wall_collision = WallCollision::NONE;
    }

}

void ResolveYCollisions(World& world, float dt, uint16_t i){
    auto& physics = world.physics;
    auto& level = world.current_level;

    //Useful data references
    float& pos_x = physics.positions[i].x;
    float& pos_y = physics.positions[i].y;
    float& vel_y = physics.velocities[i].y;
    bool& is_grounded = physics.is_grounded[i];
    float& size_x = physics.sizes[i].x;
    float& size_y = physics.sizes[i].y;
    float& coyote_timer = physics.coyote_timer[i];

    //Collision data
    float next_pos_y = pos_y + (vel_y*dt);
    bool collision_y = false;


    // CHECK COLLISIONS WHEN FALLING
    if (vel_y > 0) {
        int index_left = level.GetTileIndexAtPosition(pos_x, (next_pos_y + size_y));
        int index_right = level.GetTileIndexAtPosition((pos_x + size_x - 1),(next_pos_y + size_y));

        if (level.map[index_left] > 0 || level.map[index_right] > 0){
            int tile_row = (int)((next_pos_y + size_y) / TILE_SIZE);
            pos_y = (tile_row * TILE_SIZE) - size_y;


            collision_y = true;
            is_grounded = true;
            coyote_timer = 0.08f;
        }

    }

    //CHECK COLLISION WHEN JUMPING
    else if (vel_y < 0) {
        int index_left  = level.GetTileIndexAtPosition(pos_x , next_pos_y);
        int index_right =  level.GetTileIndexAtPosition((pos_x + size_x - 1), (next_pos_y / TILE_SIZE));

        if (level.map[index_left] > 0 || level.map[index_right] > 0) collision_y = true;
    }


    // RESOLVE BEHAVIOUR DEPENDING ON RESULTS
    if (collision_y) {
        vel_y = 0.0f;// Halt Y movement
    }
    else {
        // Just move
        pos_y = next_pos_y;
        if (vel_y > 0.1f){
            is_grounded = false;
        }
        coyote_timer -= dt;
    }

}

void ApplyFrictions(World& world, uint16_t i){
    auto& physics = world.physics;
    float& vel_x = physics.velocities[i].x;
    float& vel_y = physics.velocities[i].y;
    bool& is_grounded = physics.is_grounded[i];

    if(is_grounded){
        vel_x *=  GROUND_FRICTION;
    }else if(physics.wall_collision[i] != WallCollision::NONE){
        vel_y *= WALL_FRICTION;
    }
    else{
        vel_x *=  AIR_FRICTION;
    }
}

void UpdatePhysics(World& world, float dt){

    for(int i = 0; i < MAX_ENTITIES; i++){

        //Performance filter
        auto& physics = world.physics;
        if (!physics.active[i]) continue;

        IntegrateForces(world, dt, i);
        ResolveXCollisions(world, dt, i);
        ResolveYCollisions(world, dt, i);
        ApplyFrictions(world, i);

    }
}
