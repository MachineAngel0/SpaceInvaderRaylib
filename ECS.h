//
// Created by Adams Humbert on 4/3/2025.
//

#ifndef ECS_H
#define ECS_H
#include <cstdint>
#include <unordered_map>

#include "raylib.h"


using Entity = uint32_t;
static Entity max_entity_count = 0;

inline Entity CreateEntity()
{
    const Entity new_entity = max_entity_count++;
    return new_entity;
}

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

typedef struct ComponentRegistry

{
    std::unordered_map<Entity, Transform2DComponent> transforms;
    std::unordered_map<Entity, SpriteAtlusComponent> sprite_atlus;
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

typedef struct PlayerMovementSystem
{
    static void Update(ComponentRegistry& component_registry)
    {
        for (int i = 0; i < max_entity_count; i++)
        {
            if (!component_registry.transforms.contains(i)) continue;

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
        }
    }
} PlayerMovementSystem;

#endif //ECS_H
