//
// Created by Adams Humbert on 4/3/2025.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "ECS.h"
#include "raylib.h"


inline void CreatePlayerProjectile(ComponentRegistry& component_registry, Vector2 position)
{
    Entity projectile = CreateEntity();

    component_registry.transforms[projectile] = {
        .position = {position},
        .Velocity = {0, -300.f},

    };
    component_registry.Rectangle2DRenders[projectile] = {
        .size{10, 20},
        .color{GREEN},
    };

}


#endif //PROJECTILE_H
