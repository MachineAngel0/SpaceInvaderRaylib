//
// Created by Adams Humbert on 4/3/2025.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "raylib.h"
#include "ECS_Component.h"


inline void CreatePlayerProjectile(ComponentRegistry& component_registry, Vector2 position)
{
    Entity projectile = CreateEntity();

    component_registry.transforms[projectile] = {
        .position = {position},
        .Velocity = {0, -300.f},

    };
    component_registry.rectangle_2d_renders[projectile] = {
        .size{10, 20},
        .color{GREEN},
    };
    component_registry.collision_rectangle_2ds[projectile] = {
        .size {10,20}
    };
    component_registry.projectile_component[projectile] = {};

}


#endif //PROJECTILE_H
