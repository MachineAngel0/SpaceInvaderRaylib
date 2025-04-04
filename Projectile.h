//
// Created by Adams Humbert on 4/3/2025.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <array>

#include "Entity.h"
#include "raylib.h"


typedef struct Projectile
{
    Vector2 Position{};
    Vector2 Velocity = Vector2{0.f, 200.f};
    Vector2 Size = Vector2{5.f, 10.f};;
    bool isAlive = true;
} Projectile;

constexpr int PROJECTILE_MAX{15};
static int ProjectileArrayCount = 0;
inline std::array<Projectile, PROJECTILE_MAX> ProjectileArray;

void UpdateDrawProjectile();
void DrawProjectile(const Projectile &projectile);

void ShootProjectile(const Player &player);



void UpdateProjectile();


#endif //PROJECTILE_H
