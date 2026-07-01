#include "entity_spawner.h"
#include "raylib.h"
#include "../core/world.h"

void SpawnEntity(World& world, std::string entity_type, Vector2 position, uint16_t id){

    // INPUT COMPONENT INITIALIZATION
    if(entity_type == "player"){
        world.inputs.active[id] = true;
        world.locomotions.jumping_force[id] = world.entity_repository[entity_type].jumping_force;
        world.locomotions.wall_jumping_force[id] = world.entity_repository[entity_type].wall_jumping_force;
        world.locomotions.running_force[id] = world.entity_repository[entity_type].running_force;
        world.locomotions.air_movement_force[id] = world.entity_repository[entity_type].air_movement_force;
    }

    // AI COMPONENT INITIALIZATION
    if(entity_type != "player"){
        world.ais.active[id] = true;
        world.ais.aggro_range[id] = world.entity_repository[entity_type].aggro_range;
        world.ais.follow_speed[id] = world.entity_repository[entity_type].follow_speed;
        world.ais.patrol_speed[id] = world.entity_repository[entity_type].patrol_speed;
        world.ais.ai_arquetypes[id] = world.entity_repository[entity_type].ai_archetype;
    }

    // PHYSICS COMPONENT INITIALIZATION
    world.physics.active[id] = true;
    world.physics.positions[id].x = position.x;
    world.physics.positions[id].y = position.y;
    world.physics.sizes[id].x = world.entity_repository[entity_type].width;
    world.physics.sizes[id].y = world.entity_repository[entity_type].height;
    world.physics.mass[id] = world.entity_repository[entity_type].mass;

    // STATS COMPONENT INITIALIZATION
    world.stats.active[id] = true;
    world.stats.hp[id] = world.entity_repository[entity_type].HP;
    world.stats.max_hp[id] = world.entity_repository[entity_type].max_HP;


    // RENDER COMPONENT INITIALIZATION
    world.renders.active[id] = true;
    world.renders.asset_id[id] = world.entity_repository[entity_type].sprite_id;
    world.renders.asset_width[id] = world.entity_repository[entity_type].sprite_width;
    world.renders.asset_height[id] = world.entity_repository[entity_type].sprite_height;

    // ANIMATION COMPONENT INITIALIZAION
    world.animations.active[id] = true;
    world.animations.n_frames[id] = world.entity_repository[entity_type].n_animation_frames;
    world.animations.anim_speed[id] = world.entity_repository[entity_type].anim_speed;
}
