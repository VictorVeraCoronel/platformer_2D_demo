#include "entity_spawner.h"
#include "raylib.h"
#include "../core/world.h"

void SpawnEntity(World& world, std::string entity_type, Vector2 position, uint16_t id){

    if(entity_type == "player"){
        world.inputs.active[id] = true;
    }

    //Physics component initialization
    world.physics.active[id] = true;
    world.physics.positions[id].x = position.x;
    world.physics.positions[id].y = position.y;
    world.physics.sizes[id].x = world.entity_repository[entity_type].width;
    world.physics.sizes[id].y = world.entity_repository[entity_type].height;
    world.physics.mass[id] = world.entity_repository[entity_type].mass;

    //Stats component initialization
    world.stats.active[id] = true;
    world.stats.hp[id] = world.entity_repository[entity_type].HP;
    world.stats.jumping_force[id] = world.entity_repository[entity_type].jumping_force;
    world.stats.running_force[id] = world.entity_repository[entity_type].running_force;
    world.stats.air_movement_force[id] = world.entity_repository[entity_type].air_movement_force;
    world.stats.aggro_range[id] = world.entity_repository[entity_type].aggro_range;

    //Render component initialization
    world.renders.active[id] = true;
    world.renders.asset_id[id] = world.entity_repository[entity_type].sprite_id;
    world.renders.asset_width[id] = world.entity_repository[entity_type].sprite_width;
    world.renders.asset_height[id] = world.entity_repository[entity_type].sprite_height;

    //Render component initialization
    world.animations.active[id] = true;
    world.animations.n_frames[id] = world.entity_repository[entity_type].n_animation_frames;
    world.animations.anim_speed[id] = world.entity_repository[entity_type].anim_speed;
}
