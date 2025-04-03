#include <array>
#include <iostream>
#define RAYMATH_IMPLEMENTATION
#include "raylib.h"
#include "raymath.h"
#include "Game.h"
#include "GameWindow.h"


#define Window_Title "Space Invaders"

int main(void)
{
    InitWindow(ScreenWidth, ScreenHeight, Window_Title);

    SetTargetFPS(60);

    //init player
    Player player = PlayerStart;
    // set actual values
    // put at the center of the width, and bottom of the height
    const int ScreenHeightOffset = 20;
    player.Position = Vector2(ScreenWidth/2 - player.SpriteAtlusSize.y, ScreenHeight - player.SpriteAtlusSize.y - ScreenHeightOffset);
    player.PlayerTexture =  InitSpriteTexture(player.TextureFilePath);


    SpaceInvaderEnemy Enemy = Squid;
    Enemy.EnemyTexture =  InitSpriteTexture(Enemy.TextureFilePath);

    const uint8_t SquidEnemyAmount = 11;
    const uint8_t CrabEnemyAmount = 22;
    const uint8_t OctopusEnemyAmount = 22;
    const uint8_t EnemyTotal = SquidEnemyAmount + CrabEnemyAmount +OctopusEnemyAmount;

    // set their size apart
    uint8_t row_size = 11;
    uint8_t col_size = 4;
    std::array<SpaceInvaderEnemy, EnemyTotal> EnemyArray;

    uint8_t row = 0;
    uint8_t col = 0;
    //TODO: placement offset
    for (int i = 0; i < EnemyTotal; i++)
    {
        SpaceInvaderEnemy Temp;
        // replace these with an enum
        if (col == 0) // squid
        {
            Temp = Squid;
        }
        if (col == 1 || col == 2) // crab
        {
            Temp = Crab;
        }
        if (col == 3 || col == 4) // octo
        {
            Temp = Octopus;
        }
        Temp.EnemyTexture =  InitSpriteTexture(Temp.TextureFilePath);
        // set the position
        Temp.Position.x = row * 50 + Temp.SpriteAtlusSize.x;
        Temp.Position.y = col * 50 + Temp.SpriteAtlusSize.y;


        row++;
        if (row >= row_size)
        {
            row = 0;
            col++;
        }



        EnemyArray[i] = Temp;
    }

    // projectile array
    static int ProjectileArrayCount = 0;
    std::array<Projectile, PROJECTILE_MAX> ProjectileArray;

    //game loop
    while (!WindowShouldClose())
    {
        // input detection

        //Player Movement keys
        // TODO: Check for out of bounds, and when player is hit
        if (IsKeyDown(KEY_D))
        {
            player.Position.x += player.PlayerSpeed * GetFrameTime();
        }
        if (IsKeyDown(KEY_A))
        {
            player.Position.x -= player.PlayerSpeed * GetFrameTime();
        }

        //spawn projectile
        if (IsKeyPressed(KEY_SPACE))
        {
            Projectile proj{
                .Position = Vector2(player.Position.x+ player.SpriteAtlusSize.x, player.Position.y-25),


            };

            ProjectileArray[ProjectileArrayCount++] = proj;
            if (ProjectileArrayCount >= PROJECTILE_MAX)
            {
                ProjectileArrayCount = 0;
            }
        }

        //update loop

        //update projectile
        for (Projectile& projectile: ProjectileArray)
        {
            projectile.Position.y -= projectile.Velocity.y * GetFrameTime();

        }



        // render loop
        BeginDrawing();
        ClearBackground(BLACK);




        //DrawSprite(Enemy.EnemyTexture, Enemy.SpriteAtlusLocation, Enemy.Position, Enemy.SpriteScale);
        DrawSpriteAtlus(player.PlayerTexture, player.SpriteAtlusUVLocation, player.SpriteAtlusSize, player.Position, player.SpriteScale);

        for (SpaceInvaderEnemy& space_invader_enemy: EnemyArray)
        {
            DrawSpriteAtlus(space_invader_enemy.EnemyTexture, space_invader_enemy.SpriteAtlusUVLocation, space_invader_enemy.SpriteAtlusSize, space_invader_enemy.Position, space_invader_enemy.SpriteScale);
        }
        for (Projectile& projectile: ProjectileArray)
        {
            DrawProjectile(projectile);

        }




        // this gets drawn on top
       // DrawText("Space Invaders!", 0.f, 0.f, 20, GREEN);
        DrawText(TextFormat("FPS: %i", GetFPS()), ScreenWidth-150, 0, 20, WHITE); // Display FPS
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
