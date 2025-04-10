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

    // component registry
    ComponentRegistry component_registry;



    // player
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
    component_registry.inputs[entity_player] = InputComponent{

    };


    // Enemy
    // set their size apart
    uint8_t row_size = 11;
    uint8_t col_size = 4;


    uint8_t row = 0;
    uint8_t col = 0;

    const uint8_t SquidEnemyAmount = 11;
    const uint8_t CrabEnemyAmount = 22;
    const uint8_t OctopusEnemyAmount = 22;
    const uint8_t EnemyTotal = SquidEnemyAmount + CrabEnemyAmount + OctopusEnemyAmount;

    for (auto i = 0; i < EnemyTotal; i++)
    {
        Entity alien = CreateEntity();

        // set the position
        const int RowSpawnOffset = 50;
        const int ColSpawnOffset = 50;
        const int HorizontalScreenOffset = 50;
        const int VerticalScreenOffset = 50;
        float horizontal_location = row * RowSpawnOffset + HorizontalScreenOffset;
        float vertical_location = col * ColSpawnOffset + VerticalScreenOffset;

        // replace these with an enum
        if (col == 0) // squid
        {
            component_registry.sprite_atlus[alien] = SpriteAtlusComponent{
                .sprite_UV_location = {0, 0},
                 .sprite_size = {17, 10},
                .sprite_scale = {2, 2},
            };
        }
        if (col == 1 || col == 2) // crab
        {
            component_registry.sprite_atlus[alien] = SpriteAtlusComponent{
                .sprite_UV_location = {20, 10},
                .sprite_size = {17, 10},
                .sprite_scale = {2, 2},
            };
        }
        if (col == 3 || col == 4) // octo
        {
            component_registry.sprite_atlus[alien] = SpriteAtlusComponent{
                .sprite_UV_location = {37, 10},
                .sprite_size = {17, 10},
                .sprite_scale = {2, 2},
            };
        }

        const int screen_height_offset = 50;
        const int screen_width_offset = 50;
        component_registry.transforms[alien] = Transform2DComponent{
            .position = Vector2(horizontal_location,
                                  vertical_location),
            .Velocity = {0, 0},
        };

        component_registry.Aliens[alien];


        row++;
        if (row >= row_size)
        {
            row = 0;
            col++;
        }
    }



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
        AlienMovementSystem::Update(component_registry, game_state, SquidEnemyAmount);
        //TODO:
        //LifeTimeSystem::Update(component_registry);
        RectangleRenderSystem::Update(component_registry);

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
