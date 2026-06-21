#include "../../core/world.h"

void UpdatePhysics(World& world, float dt){

    auto& physics = world.physics;
    const float gravity = world.gravity;
    const float fall_multiplier = world.fall_gravity_multiplier;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if (!physics.active[i]) continue;//Performance filter

        //Entity mass
        float entity_mass = (physics.mass[i] > 0.0f) ? physics.mass[i] : 1.0f;

        //Apply forces
        physics.velocities[i].x += (physics.forces[i].x / entity_mass) * dt;
        physics.velocities[i].y += (physics.forces[i].y / entity_mass) * dt;


        //Clear forces
        physics.forces[i].x = 0;
        physics.forces[i].y = 0;

        //Move entity depending on velocities
        physics.positions[i].x += physics.velocities[i].x * dt;
        physics.positions[i].y += physics.velocities[i].y * dt;

        //Apply friction in x direction
        physics.velocities[i].x *=  FRICTION;

    }



}
