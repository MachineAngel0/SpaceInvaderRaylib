//
// Created by Adams Humbert on 4/3/2025.
//

#include "Projectile.h"


void UpdateDrawProjectile()
{
    for (Projectile &projectile: ProjectileArray)
    {
        DrawProjectile(projectile);
    }
}

void DrawProjectile(const Projectile &projectile)
{
    if (!projectile.isAlive) return;
    //DrawTextureRec(player.PlayerTexture, AtlusUV, Vector2{player.PlayerPos.x,player.PlayerPos.y}, WHITE);
    DrawRectangle(projectile.Position.x, projectile.Position.y, projectile.Size.x, projectile.Size.y, GREEN);
}

void ShootProjectile(const Player &player)
{
    Projectile proj{
        .Position = Vector2(player.Position.x + player.SpriteAtlusSize.x, player.Position.y - 25),
        .isAlive = true,
    };

    ProjectileArray[ProjectileArrayCount++] = proj;
    if (ProjectileArrayCount >= PROJECTILE_MAX)
    {
        ProjectileArrayCount = 0;
    }
}

void UpdateProjectile()
{
    //update projectile
    for (Projectile &projectile: ProjectileArray)
    {
        projectile.Position.y -= projectile.Velocity.y * GetFrameTime();
    }
}
