#include "../../core/world.h"
#include <iostream>

void UpdatePhysics(World& world, float dt){

    //Useful references
    auto& physics = world.physics;
    const float gravity = world.gravity;
    const float fall_multiplier = world.fall_gravity_multiplier;



    for(int i = 0; i < MAX_ENTITIES; i++){
        //std::cout<<(physics.active[i])<<std::endl;
        //std::cout<<"Fisiqueoooo: "<<i<<std::endl;


        if (!physics.active[i]) continue;//Performance filter

        //Check if player touchs ground
        if(physics.positions[i].y >= (850-256) && !physics.is_grounded[i]){
            physics.velocities[i].y = 0;
            physics.is_grounded[i] = true;
        }

        if(physics.positions[i].y < (850-256)){
            physics.is_grounded[i] = false;
        }

        //Entity mass
        float entity_mass = (physics.mass[i] > 0.0f) ? physics.mass[i] : 1.0f;

        //Calculate current gravity
        float current_gravity;
        if(!physics.is_grounded[i]){
            current_gravity = (physics.velocities[i].y > 0.0f) ? gravity * fall_multiplier : gravity;
        }else{
            current_gravity = 0;
        }

        //Add gravity to y forces
        physics.forces[i].y += (entity_mass * current_gravity);

        //Apply forces
        physics.velocities[i].x += (physics.forces[i].x / entity_mass) * dt;
        physics.velocities[i].y += (physics.forces[i].y / entity_mass) * dt;

        //Clear forces
        physics.forces[i].x = 0;
        physics.forces[i].y = 0;

        //Move entity depending on velocities
        physics.positions[i].x += physics.velocities[i].x * dt;
        physics.positions[i].y += physics.velocities[i].y * dt;

        //Apply frictions with ground and air
        if(physics.is_grounded[i]){
            physics.velocities[i].x *=  GROUND_FRICTION;
        }else{
            physics.velocities[i].x *=  AIR_FRICTION;
        }




    }

    // std::cout<<"X: "<<physics.positions[0].x<<std::endl;
    // std::cout<<"Y: "<<physics.positions[0].y<<std::endl;
    // std::cout<<std::endl;



}
