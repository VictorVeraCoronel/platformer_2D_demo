#include "../../core/world.h"
#include "animation_system.h"

void UpdateAnimationSystem(World& world, float dt) {
    for (int i = 0; i < MAX_ENTITIES; i++) {

        // Si la entidad tiene más de 1 frame, es animable
        if (world.animations.n_frames[i] > 1) {
            world.animations.timer[i] += dt;

            if (world.animations.timer[i] >= world.animations.anim_speed[i]) {
                world.animations.timer[i] = 0.0f;
                world.animations.current_frame[i]++;

                // Volver al inicio si llegamos al final (Loop)
                if (world.animations.current_frame[i] >= world.animations.n_frames[i]) {
                    world.animations.current_frame[i] = 0;
                }
            }
        }
    }
}
