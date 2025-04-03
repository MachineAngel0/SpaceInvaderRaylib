//
// Created by Adams Humbert on 4/1/2025.
//

#ifndef GAME_H
#define GAME_H

#include "GameWindow.h"
#include "raylib.h"

#define PROJECTILE_MAX (15)

enum things
{
    First,
    Second,
    Third,
};


typedef struct Player
{
    Vector2 Position{};
    Texture2D PlayerTexture{};
    const char *TextureFilePath = "Assets/SpaceInvaders_SpriteSheet.png";
    //UV Location
    Vector2 SpriteAtlusUVLocation{0, 50};
    //width height
    Vector2 SpriteAtlusSize{17, 10};
    Vector2 SpriteScale = {2, 2};

    float PlayerSpeed{50.f};
} Player;


static const Player PlayerStart = {
    //TODO: set starting location
    .Position = (ScreenWidth / 2, ScreenHeight / 2),
    .PlayerTexture = 0,
    .PlayerSpeed = 50.0f

};


typedef struct SpaceInvaderEnemy
{
    Vector2 Position = {0, 0};
    //this is just here for now, but i could move it to a more global space
    Vector2 EnemyOffset = Vector2(10, 10); //diagonal for now
    Texture2D EnemyTexture;
    const char *TextureFilePath = "Assets/SpaceInvaders_SpriteSheet.png";
    //UV Location
    Vector2 SpriteAtlusUVLocation{0, 0};
    //width height
    Vector2 SpriteAtlusSize{17, 10};
    Vector2 SpriteScale = {2, 2};
    float EnemySpeed = 50.0f;
} SpaceInvaderEnemy;


// squid top row, crab next two rows, octopus last two rows
static const SpaceInvaderEnemy Squid = {
    .SpriteAtlusUVLocation = {0, 0},
    .SpriteAtlusSize = {17, 10},
};

static const SpaceInvaderEnemy Crab = {
    .SpriteAtlusUVLocation = {20, 0},
    .SpriteAtlusSize = {17, 10},
};
static const SpaceInvaderEnemy Octopus = {
    .SpriteAtlusUVLocation = {37, 0},
    .SpriteAtlusSize = {17, 10},
};


Texture2D InitSpriteTexture(const char *TextureFilePath);

void DrawSpriteAtlus(const Texture2D &SpriteTexture, const Vector2 SpriteAtlusUVLocation,
                const Vector2 SpriteAtlusSize, const Vector2 SpritePosition,
                const Vector2 SpriteScale);




typedef struct Projectile
{
    Vector2 Position;
    Vector2 Velocity = Vector2{0.f, 200.f};
    Vector2 Size = Vector2{5.f, 10.f};;

} Projectile;

void DrawProjectile(const Projectile& projectile);

#endif //GAME_H
