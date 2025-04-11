//
// Created by Adams Humbert on 4/3/2025.
//

#ifndef ECS_H
#define ECS_H
#include <array>
#include <cstdint>
#include <iostream>
#include <unordered_map>

#include "ECS_Entity.h"
#include "cmake-build-debug/_deps/raylib-src/src/raylib.h"


/* COMPONENTS */

struct Transform2DComponent;
struct SpriteAtlusComponent;
struct AlienComponent;
struct InputComponent;
struct LifeTimeComponent;
struct Rectangle2DComponent;
struct CollisionRectangle2DComponent;
struct ProjectileComponent;


typedef struct ComponentRegistry
{
    std::unordered_map<Entity, Transform2DComponent> transforms;
    std::unordered_map<Entity, SpriteAtlusComponent> sprite_atlus;
    std::unordered_map<Entity, AlienComponent> aliens;
    std::unordered_map<Entity, InputComponent> inputs;
    std::unordered_map<Entity, LifeTimeComponent> life_times;
    std::unordered_map<Entity, Rectangle2DComponent> rectangle_2d_renders;
    std::unordered_map<Entity, CollisionRectangle2DComponent> collision_rectangle_2ds;
    std::unordered_map<Entity, ProjectileComponent>  projectile_component;

    /*testing*/
    //std::array<ProjectileComponent, max_entity_amount>  projectile_component_array;
} ComponentRegistry;




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

typedef struct ProjectileComponent
{
} ProjectileComponent;

typedef struct InputComponent
{
} InputComponent;

typedef struct LifeTimeComponent
{
    float LifeTime{};
    //when to delete the entity
    float LifeTimeTrigger{};
} LifeTimeComponent;

typedef struct CollisionRectangle2DComponent
{
    Vector2 size{0, 0};
} CollisionRectangle2DComponent;









#endif //ECS_H
