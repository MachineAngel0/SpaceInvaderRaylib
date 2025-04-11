//
// Created by Adams Humbert on 4/9/2025.
//

#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H
#include "ECS_Component.h"
#include "Game.h"
#include "GameWindow.h"
#include "Projectile.h"


typedef struct TransformSystem
{
    // we'll use a constant time for this demonstration

    static void Update(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.transforms.contains(i)) continue;

            component_registry.transforms[i].position.x += component_registry.transforms[i].Velocity.x *
                    GetFrameTime();
            component_registry.transforms[i].position.y += component_registry.transforms[i].Velocity.y *
                    GetFrameTime();
        }
    }
} TransformSystem;


typedef struct SpriteSystem
{
    //update sprite positions
    static void Init(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.sprite_atlus.contains(i)) continue;

            //load in the texture
            component_registry.sprite_atlus[i].sprite_texture = LoadTexture(
                component_registry.sprite_atlus[i].TextureFilePath);
        }
    }

    //update sprite positions
    static void Update(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.sprite_atlus.contains(i) || !component_registry.transforms.contains(i)) continue;

            component_registry.transforms[i].position.x += component_registry.transforms[i].Velocity.x *
                    GetFrameTime();
            component_registry.transforms[i].position.y += component_registry.transforms[i].Velocity.y *
                    GetFrameTime();
        }
    }


    static void Draw(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.sprite_atlus.contains(i) || !component_registry.transforms.contains(i)) continue;

            SpriteAtlusComponent sprite = component_registry.sprite_atlus[i];
            Transform2DComponent transform = component_registry.transforms[i];

            const Rectangle AtlusUV = {
                sprite.sprite_UV_location.x, sprite.sprite_UV_location.y, sprite.sprite_size.x, sprite.sprite_size.y
            };
            const Rectangle Dest = {
                transform.position.x, transform.position.y, AtlusUV.width * sprite.sprite_scale.x,
                AtlusUV.height * sprite.sprite_scale.y
            };
            DrawTexturePro(sprite.sprite_texture, AtlusUV, Dest, Vector2{0, 0}, 0, GREEN);
            // here for debugging
            //DrawRectangle(transform.position.x, transform.position.y, sprite.sprite_size.x * sprite.sprite_scale.x, sprite.sprite_size.y * sprite.sprite_scale.y, RED);
        }
    }
} SystemsList;


typedef struct PlayerMovementSystem
{
    static void Update(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.transforms.contains(i) || !component_registry.inputs.contains(i)) continue;

            Transform2DComponent& transform_2d_component = component_registry.transforms[i];
            const float PlayerSpeed = 200;
            if (IsKeyDown(KEY_D))
            {
                transform_2d_component.Velocity.x = 200;
            }
            if (IsKeyReleased(KEY_D))
            {
                transform_2d_component.Velocity.x = 0;
            }
            if (IsKeyDown(KEY_A))
            {
                transform_2d_component.Velocity.x = -200;
            }
            if (IsKeyReleased(KEY_A))
            {
                transform_2d_component.Velocity.x = 0;
            }
            if (IsKeyPressed(KEY_SPACE))
            {
                //TODO: Spawn projectile at player location
                CreatePlayerProjectile(component_registry, {
                                           transform_2d_component.position.x, transform_2d_component.position.y - 50
                                       });
            }
        }
    }
} PlayerMovementSystem;


typedef struct AlienMovementSystem
{
    static void Update(ComponentRegistry& component_registry, GameState& game_state, int SquidEnemyAmount)
    {

        float move_down_amount = 300.f;
        bool move_down_flag = false;
        float alien_speed = 50.f;

        // get the first alien component
        // then get the x number of aline from the first to the last of the first row
        // since they are all made at the same time, it should be relatively easy

        //TODO: pass in the first and second alien, since they are never going to change
        Entity FirstAlien{0};
        Entity SecondAlien{0};
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.transforms.contains(i) || !component_registry.aliens.contains(i)) continue;
            FirstAlien = i;
            break;
        }

        // get the last alien in the first row
        SecondAlien = FirstAlien + SquidEnemyAmount - 1;


        if (component_registry.transforms[SecondAlien].position.x +
            (component_registry.sprite_atlus[SecondAlien].sprite_size.x *
             component_registry.sprite_atlus[SecondAlien].sprite_scale.x)
            >= ScreenWidth)
        {
            game_state.enemy_direction = Left;
            move_down_flag = true;
        }
        if (component_registry.transforms[FirstAlien].position.x <= 0)
        {
            game_state.enemy_direction = Right;
            move_down_flag = true;
        }


        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.transforms.contains(i) || !component_registry.aliens.contains(i)) continue;

            Transform2DComponent& transform_2d_component = component_registry.transforms[i];


            switch (game_state.enemy_direction)
            {
                case Left:
                    transform_2d_component.position.x -= alien_speed * GetFrameTime();
                    break;
                case Right:
                    transform_2d_component.position.x += alien_speed * GetFrameTime();
                    break;
                default:
                    break;
            }

            if (move_down_flag)
            {
                component_registry.transforms[i].position.y += move_down_amount * GetFrameTime();
            }
        }
        // set the flag to false at the end
        if (move_down_flag)
        {
            move_down_flag = false;
            //TODO:
            // increment a count
            // and then kill the player if it reaches a certain amount
        }
    }
} AlienMovementSystem;

typedef struct RectangleRenderSystem
{
    static void Update(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.transforms.contains(i) || !component_registry.rectangle_2d_renders.contains(i))
                continue;

            Transform2DComponent& transform_2d_component = component_registry.transforms[i];
            Rectangle2DComponent& rectangle_2d_component = component_registry.rectangle_2d_renders[i];

            DrawRectangle(transform_2d_component.position.x, transform_2d_component.position.y,
                          rectangle_2d_component.size.x, rectangle_2d_component.size.y, rectangle_2d_component.color);
        }
    }
} RectangleRenderSystem;

typedef struct CollisionRectangleCollisionSystem
{
    static void Update(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            //projectile to enemy check
            if (!component_registry.collision_rectangle_2ds.contains(i) || !component_registry.transforms.contains(i) || !component_registry.projectile_component.contains(i))
                continue;

            for (int j = 0; j < max_entity_count; j++)
            {
                if (!component_registry.collision_rectangle_2ds.contains(j) || !component_registry.transforms.contains(i) || !component_registry.sprite_atlus.contains(j) || !component_registry.aliens.contains(j))
                    continue;
                CollisionRectangle2DComponent projectile_collision = component_registry.collision_rectangle_2ds[i];
                Rectangle2DComponent projectile_rectangle_2d_component = component_registry.rectangle_2d_renders[i];
                Transform2DComponent projectile_transform = component_registry.transforms[i];
                Rectangle projectile_rectangle{projectile_transform.position.x, projectile_transform.position.y,
                              projectile_collision.size.x,projectile_collision.size.y };

                CollisionRectangle2DComponent enemy_collision = component_registry.collision_rectangle_2ds[j];
                Transform2DComponent enemy_transform = component_registry.transforms[j];
                SpriteAtlusComponent enemy_sprite = component_registry.sprite_atlus[j];
                Rectangle enemy_rectangle{enemy_transform.position.x, enemy_transform.position.y,
                              enemy_collision.size.x * enemy_sprite.sprite_scale.x, enemy_collision.size.y* enemy_sprite.sprite_scale.y};

                if (CheckCollisionRecs(projectile_rectangle, enemy_rectangle))
                {
                    std::cout << "Collision detected\n";
                    component_registry.sprite_atlus[j].sprite_scale = Vector2{0,0};
                }

            }

        }
    }
} CollisionRectangleCollisionSystem;


#endif //ECS_SYSTEM_H
