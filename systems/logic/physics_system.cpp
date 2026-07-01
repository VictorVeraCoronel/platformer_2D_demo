#include "physics_system.h"
#include <cmath>
#include <iostream>
#include <raylib.h>


void IntegrateForces(World& world, float dt){
    auto& physics = world.physics;

    const float gravity = world.gravity;
    const float fall_multiplier = world.fall_gravity_multiplier;


    for(int i = 0; i < MAX_ENTITIES; i++){
        if (!physics.active[i]) continue;
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
        if(has_desired_position){
            pos_x = desired_pos_x;
            pos_y = desired_pos_y;
            has_desired_position = false;
        }

        // APPLY GRAVITY FORCE
        forces_y += (entity_mass * current_gravity) * dt;

        // WE SUM THE FORCES OBTAINED FROM GAMEPLAY SYSTEM
        vel_x += (forces_x / entity_mass) * dt;
        vel_y += (forces_y / entity_mass);

        // CLEAR ALL FORCES
        forces_x = 0;
        forces_y = 0;


    }



};

// TILEMAP COLLISIONS
void ResolveXCollisions(World& world, float dt){
    auto& physics = world.physics;
    auto& level = world.current_level;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if (!physics.active[i]) continue;


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
            physics.wall_collision[i] = WallCollision::NONE;
        }

    }



}

// TILEMAP COLLISIONS
void ResolveYCollisions(World& world, float dt){
    auto& physics = world.physics;
    auto& level = world.current_level;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if (!physics.active[i]) continue;

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
            int index_right =  level.GetTileIndexAtPosition((pos_x + size_x - 1), (next_pos_y));

            if (level.map[index_left] > 0 || level.map[index_right] > 0) collision_y = true;
        }


        // RESOLVE BEHAVIOUR DEPENDING ON RESULTS
        if (collision_y) {
            vel_y = 0.0f;// Halt Y movement
        }
        else {
            // Just move
            pos_y = next_pos_y;
            is_grounded = false;
            coyote_timer -= dt;
        }

    }
}

// ENEMY COLLISIONS
void EnemyCollisions(World& world, float dt){
    auto& physics = world.physics;
    auto& stats = world.stats;

    for(int i = 0; i < MAX_PLAYERS; i++){
        if (!physics.active[i]) continue;

        for(int j = MAX_PLAYERS; j < MAX_ENTITIES; j++){
            if (!physics.active[j]) continue;

            // Useful references
            Vector2& player_pos = physics.positions[i];
            Vector2& player_size = physics.sizes[i];
            Rectangle player_rec = {player_pos.x, player_pos.y, player_size.x, player_size.y};
            float& player_pending_damage = stats.pending_damage[i];
            float& player_inmune_timer = stats.inmune_timer[i];
            Vector2& enemy_pos = physics.positions[j];
            Vector2& enemy_size = physics.sizes[j];
            Rectangle enemy_rec = {enemy_pos.x, enemy_pos.y, enemy_size.x, enemy_size.y};
            float& enemy_pending_damage = stats.pending_damage[j];
            Vector2& player_vel = physics.velocities[i];



            if(player_vel.y > 0.0f){

                float offset = 6.0f;
                bool jumping_on_head = (player_pos.y + player_size.y) < (enemy_pos.y + offset);
                bool collision_detected = CheckCollisionRecs(player_rec, enemy_rec);

                if(jumping_on_head && collision_detected && enemy_pending_damage == 0){
                    enemy_pending_damage += 1;
                    player_inmune_timer = 0.2f; //Little time with inmunity to avoid receiving damage by mistake
                    player_vel.y = -world.locomotions.jumping_force[i];
                }else if (collision_detected){
                    player_pending_damage += 1;
                    player_vel.y = -world.locomotions.jumping_force[i]/3;
                    player_vel.x = -player_vel.x * 2;
                }

            }
            else{
                bool collision_detected = CheckCollisionRecs(player_rec, enemy_rec);

                if(collision_detected){
                    player_pending_damage += 1;
                    player_vel.y = -world.locomotions.jumping_force[i]/3;
                    player_vel.x = -player_vel.x * 2;
                }

            }





        }

    }

}

void ApplyFrictions(World& world, float dt){
    auto& physics = world.physics;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if (!physics.active[i]) continue;

        float& vel_x = physics.velocities[i].x;
        float& vel_y = physics.velocities[i].y;
        bool& is_grounded = physics.is_grounded[i];

        if(is_grounded){
            vel_x *= std::pow(GROUND_FRICTION, dt * 60.0f);
        }else if(physics.wall_collision[i] != WallCollision::NONE){
            vel_y *= std::pow(WALL_FRICTION, dt * 60.0f);
        }
        else{
            vel_x *=  std::pow(AIR_FRICTION, dt * 60.0f);
        }

    }


}

void UpdatePhysics(World& world, float dt){

    IntegrateForces(world, dt);
    ResolveXCollisions(world, dt);
    ResolveYCollisions(world, dt);
    EnemyCollisions(world, dt);
    ApplyFrictions(world, dt);
}
