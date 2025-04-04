#include <array>
#include <iostream>
#include "raylib.h"
#include "Game.h"
#include "GameWindow.h"
#include "Projectile.h"
#include "Entity.h"


#define Window_Title "Space Invaders"


int main(void)
{
    InitWindow(ScreenWidth, ScreenHeight, Window_Title);

    SetTargetFPS(60);

    // GameState
    GameState game_state;


    Player player = InitPlayer();


    InitEnemies();

    //game loop
    while (!WindowShouldClose())
    {
        // input detection

        //Player Movement keys
        // TODO: Check for out of bounds, and when player is hit
        if (IsKeyDown(KEY_D))
        {
            MoveRight(player);
        }
        if (IsKeyDown(KEY_A))
        {
            MoveLeft(player);
        }
        //spawn projectile
        if (IsKeyPressed(KEY_SPACE))
        {
            ShootProjectile(player);
        }

        // projectile to enemies collision
        for (auto &enemy: EnemyArray)
        {
            for (auto &projectile: ProjectileArray)
            {
                if (!projectile.isAlive) continue;
                if (CheckCollisionRecs(
                        Rectangle{projectile.Position.x, projectile.Position.y, projectile.Size.x, projectile.Size.y},
                        Rectangle{
                            enemy.Position.x, enemy.Position.y, enemy.SpriteAtlusSize.x * enemy.SpriteScale.x,
                            enemy.SpriteAtlusSize.y * enemy.SpriteScale.x
                        })
                    && enemy.isAlive)

                {
                    printf("hit\n");

                    DespawnEnemy(enemy);

                    projectile.isAlive = false;
                    game_state.score++;
                }

                // for debugging
                //DrawRectangle(projectile.Position.x, projectile.Position.y, projectile.Size.x, projectile.Size.y, RED);
                //DrawRectangle(enemy.Position.x, enemy.Position.y, enemy.SpriteAtlusSize.x*enemy.SpriteScale.x, enemy.SpriteAtlusSize.y*enemy.SpriteScale.x, RED);
            }
        }
        for (auto &enemy: EnemyArray)
        {
            // if any
        }

        /*update loop*/

        //update projectile
        UpdateProjectile();


        // render loop
        BeginDrawing();
        ClearBackground(BLACK);


        //DrawSprite(Enemy.EnemyTexture, Enemy.SpriteAtlusLocation, Enemy.Position, Enemy.SpriteScale);
        DrawSpriteAtlus(player.PlayerTexture, player.SpriteAtlusUVLocation, player.SpriteAtlusSize, player.Position,
                        player.SpriteScale);

        UpdateEnemy();
        UpdateDrawProjectile();


        // this gets drawn on top
        // DrawText("Space Invaders!", 0.f, 0.f, 20, GREEN);
        DrawText(TextFormat("FPS: %i", GetFPS()), ScreenWidth - 150, 20, 20, WHITE); // Display FPS
        DrawText(TextFormat("Score: %i", game_state.score), 20, 20, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
