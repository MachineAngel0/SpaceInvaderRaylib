#include <array>
#include <iostream>

#include "ECS.h"
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

    ComponentRegistry component_registry;

    Entity entity_player = CreateEntity();
    component_registry.sprite_atlus[entity_player] = SpriteAtlusComponent{
        .sprite_UV_location = {0, 50},
        .sprite_size = {17, 10},
        .sprite_scale = {2, 2},
    };
    const int ScreenHeightOffset = 20;
    component_registry.transforms[entity_player] = Transform2DComponent{
        .position = Vector2(ScreenWidth / 2 - component_registry.sprite_atlus[entity_player].sprite_size.y,
                              ScreenHeight - component_registry.sprite_atlus[entity_player].sprite_size.y - ScreenHeightOffset),
        .Velocity = {0, 0},
    };

    //Init
    SpriteSystem::Init(component_registry);

    //game loop
    while (!WindowShouldClose())
    {
        // input detection

        //Player Movement keys
        // TODO: Check for out of bounds, and when player is hit
        if (IsKeyDown(KEY_D))
        {
        }
        if (IsKeyDown(KEY_A))
        {
        }
        //spawn projectile
        if (IsKeyPressed(KEY_SPACE))
        {
        }

        /*update loop*/

        TransformSystem::Update(component_registry);
        SpriteSystem::Update(component_registry);
        PlayerMovementSystem::Update(component_registry);

        // render loop
        BeginDrawing();
        ClearBackground(BLACK);

        SpriteSystem::Draw(component_registry);

        // this gets drawn on top
        // DrawText("Space Invaders!", 0.f, 0.f, 20, GREEN);
        DrawText(TextFormat("FPS: %i", GetFPS()), ScreenWidth - 150, 20, 20, WHITE); // Display FPS
        DrawText(TextFormat("Score: %i", game_state.score), 20, 20, 20, WHITE);
        EndDrawing();
    }


    CloseWindow();

    return 0;
}
