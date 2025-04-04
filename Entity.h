//
// Created by Adams Humbert on 4/3/2025.
//


#ifndef ENTITY_H
#define ENTITY_H
#include <array>
#include <cstdint>

#include "GameWindow.h"
#include "raylib.h"


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

    float PlayerSpeed{200.f};
} Player;


static const Player PlayerStart = {
    //TODO: set starting location
    .Position = (ScreenWidth / 2, ScreenHeight / 2),
    .PlayerTexture = 0,

};


Player InitPlayer();

void MoveLeft(Player &player);

void MoveRight(Player &player);


typedef struct SpaceInvaderEnemy
{
    Vector2 Position = {0, 0};
    //this is just here for now, but i could move it to a more global space
    Texture2D EnemyTexture{};
    const char *TextureFilePath = "Assets/SpaceInvaders_SpriteSheet.png";
    //UV Location
    Vector2 SpriteAtlusUVLocation{0, 0};
    Vector2 SpriteAtlusUVLocation2{0, 0}; // for when the enemy moves
    //width height
    Vector2 SpriteAtlusSize{17, 10};
    Vector2 SpriteScale = {2, 2};
    float EnemySpeed = 50.0f;
    bool isAlive = true;
} SpaceInvaderEnemy;


// squid top row, crab next two rows, octopus last two rows
static const SpaceInvaderEnemy Squid = {
    .SpriteAtlusUVLocation = {0, 0},
    .SpriteAtlusUVLocation2 = {0, 10},
    .SpriteAtlusSize = {17, 10},
};

static const SpaceInvaderEnemy Crab = {
    .SpriteAtlusUVLocation = {20, 0},
    .SpriteAtlusUVLocation2 = {20, 10},
    .SpriteAtlusSize = {17, 10},
};
static const SpaceInvaderEnemy Octopus = {
    .SpriteAtlusUVLocation = {37, 0},
    .SpriteAtlusUVLocation2 = {37, 10},
    .SpriteAtlusSize = {17, 10},
};


static int MoveCount = 0;
static int DeathMoveCountTrigger = 5;
inline int EnemyDirection = 1;
const uint8_t SquidEnemyAmount = 11;
const uint8_t CrabEnemyAmount = 22;
const uint8_t OctopusEnemyAmount = 22;
const uint8_t EnemyTotal = SquidEnemyAmount + CrabEnemyAmount + OctopusEnemyAmount;
inline std::array<SpaceInvaderEnemy, EnemyTotal> EnemyArray;

void InitEnemies();

void UpdateEnemy();

void DespawnEnemy(SpaceInvaderEnemy &Enemy);

void MoveEnemiesDown(float movedownamount = 5.f);

Texture2D InitSpriteTexture(const char *TextureFilePath);

void DrawSpriteAtlus(const Texture2D &SpriteTexture, const Vector2 SpriteAtlusUVLocation,
                     const Vector2 SpriteAtlusSize, const Vector2 SpritePosition,
                     const Vector2 SpriteScale);


#endif //ENTITY_H
