//
// Created by Adams Humbert on 4/3/2025.
//

#ifndef ECS_H
#define ECS_H
#include <array>
#include <cstdint>
#include <unordered_map>

#include "Game.h"
#include "GameWindow.h"
#include "raylib.h"


using Entity = uint32_t;
static Entity max_entity_count = 0;

inline Entity CreateEntity()
{
    const Entity new_entity = max_entity_count++;
    return new_entity;
}


/* COMPONENTS */


typedef struct Transform2DComponent
{
    Vector2 position{};
    Vector2 Velocity{};
    //Vector2 rotation;
} Transform2D;


typedef struct SpriteAtlusComponent
{
    const char* TextureFilePath = "Assets/SpaceInvaders_SpriteSheet.png";
    Texture2D sprite_texture{};
    Vector2 sprite_UV_location{};
    Vector2 sprite_size{};
    Vector2 sprite_scale{};
} SpriteAtlusComponent;

typedef struct Rectangle2DComponent
{
    Vector2 size{0, 0};
    Color color{GREEN};
} Rectangle2DComponent;


typedef struct AlienComponent
{
} AlienComponent;

typedef struct InputComponent
{
} InputComponent;

typedef struct LifeTimeComponent
{
    float LifeTime{};
    //when to delete the entity
    float LifeTimeTrigger{};
} LifeTimeComponent;


typedef struct ComponentRegistry

{
    std::unordered_map<Entity, Transform2DComponent> transforms;
    std::unordered_map<Entity, SpriteAtlusComponent> sprite_atlus;
    std::unordered_map<Entity, AlienComponent> Aliens;
    std::unordered_map<Entity, InputComponent> inputs;
    std::unordered_map<Entity, LifeTimeComponent> LifeTimes;
    std::unordered_map<Entity, Rectangle2DComponent> Rectangle2DRenders;
} ComponentRegistry;


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
        }
    }
} SystemsList;

void CreatePlayerProjectile(ComponentRegistry& component_registry, Vector2 position);

typedef struct PlayerMovementSystem
{
    static void Update(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.transforms.contains(i) || !component_registry.inputs.contains(i)) continue;

            Transform2DComponent& transform_2d_component = component_registry.transforms[i];

            if (IsKeyDown(KEY_D))
            {
                transform_2d_component.Velocity.x = 50;
            }
            if (IsKeyReleased(KEY_D))
            {
                transform_2d_component.Velocity.x = 0;
            }
            if (IsKeyDown(KEY_A))
            {
                transform_2d_component.Velocity.x = -50;
            }
            if (IsKeyReleased(KEY_A))
            {
                transform_2d_component.Velocity.x = 0;
            }
            if (IsKeyPressed(KEY_SPACE))
            {
                //TODO: Spawn projectile at player location
                CreatePlayerProjectile(component_registry, {transform_2d_component.position.x, transform_2d_component.position.y - 50});
            }
        }
    }
} PlayerMovementSystem;


typedef struct AlienMovementSystem
{
    static void Update(ComponentRegistry& component_registry, GameState& game_state, int SquidEnemyAmount)
    {
        // this is kinda bad but getting the first alien manually and then getting the last alien,
        // maybe these can be specific components

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
            if (!component_registry.transforms.contains(i) || !component_registry.Aliens.contains(i)) continue;
            FirstAlien = i;
            break;
        }

        // get the last alien in the first row
        SecondAlien = FirstAlien + SquidEnemyAmount -1;


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
            if (!component_registry.transforms.contains(i) || !component_registry.Aliens.contains(i)) continue;

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
            if (!component_registry.transforms.contains(i) || !component_registry.Rectangle2DRenders.contains(i))
                continue;

            Transform2DComponent& transform_2d_component = component_registry.transforms[i];
            Rectangle2DComponent& rectangle_2d_component = component_registry.Rectangle2DRenders[i];

            DrawRectangle(transform_2d_component.position.x, transform_2d_component.position.y,
                          rectangle_2d_component.size.x, rectangle_2d_component.size.y, rectangle_2d_component.color);
        }
    }
} RectangleRenderSystem;


#endif //ECS_H
