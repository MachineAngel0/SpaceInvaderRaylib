//
// Created by Adams Humbert on 4/1/2025.
//

#ifndef GAME_H
#define GAME_H
#include <string>

#include "raylib.h"

inline float ScreenWidth;
inline float ScreenHeight;

typedef struct Player
{
    Vector2 PlayerPos;
    Texture2D PlayerTexture;
    std::string TextureFilePath = "Assets/SpaceInvaders_SpriteSheet.png";
    Vector2 SpriteAtlusLocation{0, 0};

    float PlayerSpeed{50.f};
} Player;


static const Player DefaultPlayerstate = {
    .PlayerPos = (ScreenWidth / 2, ScreenHeight / 2),
    .PlayerTexture = 0,
    .PlayerSpeed = 50.0f

};


typedef struct SpaceInvaderEnemy
{
    Vector2 EnemyPos;
    //this is just here for now, but i could move it to a more global space
    Vector2 EnemyOffset = Vector2(10, 10);//diagonal for now
    Texture2D EnemyTexture;
    std::string TextureFilePath = "Assets/SpaceInvaders_SpriteSheet.png";
    Vector2 SpriteAtlusLocation = {0, 0};
    float EnemySpeed = 50.0f;
} SpaceInvaderEnemy;


// squid top row, crab next two rows, octopus last two rows

static const SpaceInvaderEnemy Squid = {
    .SpriteAtlusLocation = {17, 10},
};
static const SpaceInvaderEnemy Crab = {
    .SpriteAtlusLocation = {0, 0},
};
static const SpaceInvaderEnemy Octopus = {
    .SpriteAtlusLocation = {0, 0},
};

#endif //GAME_H
