#include "render_entities.h"

void RenderEntities(const World& world){
    auto& renders = world.renders;

    for(int i = 0; i < MAX_ENTITIES; i++){
        if(!renders.active[i]) continue;

        auto& physics = world.physics;
        auto& anim = world.animations;
        auto& sprites = world.asset_repository.sprite;

        float width_sign = 1.0f; // 1.0f = RIGHT, -1.0f = LEFT

        if (physics.velocities[i].x > 10.0f) {
            width_sign = 1.0f;
        }
        else if (physics.velocities[i].x < -10.0f) {
            width_sign = -1.0f;
        }
        // SI EL PERSONAJE NO SE MUEVE HORIZONTALMENTE... PERO ESTÁ EN LA PARED:
        else if (physics.wall_collision[i] != WallCollision::NONE) {

            // Si la pared está a la DERECHA, el stickman debe mirar hacia la DERECHA (hacia el muro)
            if (physics.wall_collision[i] == WallCollision::RIGHT) {
                width_sign = 1.0f;
            }
            // Si la pared está a la IZQUIERDA, el stickman debe mirar hacia la IZQUIERDA
            else if (physics.wall_collision[i] == WallCollision::LEFT) {
                width_sign = -1.0f;
            }
        }


        float source_x = anim.current_frame[i] * renders.asset_width[i];
        float source_y = (float)anim.state[i] * renders.asset_height[i];
        Rectangle source_rec = { source_x, source_y, (float)renders.asset_width[i] * width_sign, (float)renders.asset_height[i] };

        Texture2D texture = sprites[renders.asset_id[i]];
        Rectangle dest_rec = { physics.positions[i].x, physics.positions[i].y, (float)renders.asset_width[i], (float)renders.asset_height[i] };
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(texture, source_rec, dest_rec, origin, 0.0f, WHITE);

    }

}
