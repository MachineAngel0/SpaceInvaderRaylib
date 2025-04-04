//
// Created by Adams Humbert on 4/3/2025.
//

#include "Entity.h"

#include <array>
#include <cstdio>


Player InitPlayer()
{
    //init player
    Player player = PlayerStart;
    // set actual values
    // put at the center of the width, and bottom of the height
    const int ScreenHeightOffset = 20;
    player.Position = Vector2(ScreenWidth / 2 - player.SpriteAtlusSize.y,
                              ScreenHeight - player.SpriteAtlusSize.y - ScreenHeightOffset);
    player.PlayerTexture = InitSpriteTexture(player.TextureFilePath);

    return player;
}

void MoveLeft(Player &player)
{
    player.Position.x -= player.PlayerSpeed * GetFrameTime();
}

void MoveRight(Player &player)
{
    player.Position.x += player.PlayerSpeed * GetFrameTime();
}

void InitEnemies()
{
    // set their size apart
    uint8_t row_size = 11;
    uint8_t col_size = 4;


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
        Temp.EnemyTexture = InitSpriteTexture(Temp.TextureFilePath);
        // set the position
        const int RowSpawnOffset = 50;
        const int ColSpawnOffset = 50;
        const int HorizontalScreenOffset = 50;
        const int VerticalScreenOffset = 50;
        Temp.Position.x = row * RowSpawnOffset + HorizontalScreenOffset;
        Temp.Position.y = col * ColSpawnOffset + VerticalScreenOffset;


        row++;
        if (row >= row_size)
        {
            row = 0;
            col++;
        }


        EnemyArray[i] = Temp;
    }
}


void UpdateEnemy()
{
    //enemy update
    for (SpaceInvaderEnemy &space_invader_enemy: EnemyArray)
    {
        space_invader_enemy.Position.x += space_invader_enemy.EnemySpeed * EnemyDirection * GetFrameTime();

        //check if the last alien has hit the edge of the screen
        SpaceInvaderEnemy LastEnemy = EnemyArray[EnemyTotal - 1];
        if (LastEnemy.Position.x + LastEnemy.SpriteAtlusSize.x * LastEnemy.SpriteScale.x >= ScreenWidth)
        {
            printf("offscreen right \n");
            EnemyDirection = -1;
            MoveEnemiesDown();

        }
        SpaceInvaderEnemy FirstEnemy = EnemyArray[0];
        if (FirstEnemy.Position.x <= 0)
        {
            printf("offscreen left\n");
            EnemyDirection = 1;
            MoveEnemiesDown();
        }

        DrawSpriteAtlus(space_invader_enemy.EnemyTexture, space_invader_enemy.SpriteAtlusUVLocation,
                            space_invader_enemy.SpriteAtlusSize, space_invader_enemy.Position,
                            space_invader_enemy.SpriteScale);
    }
}

void DespawnEnemy(SpaceInvaderEnemy &Enemy)
{
    //disable enemy so it doesn't get drawn and set size to 0
    Enemy.isAlive = false;
    Enemy.SpriteScale = {0, 0};
}

void MoveEnemiesDown( float movedownamount)
{
    //duplicate function below
    for (auto &enemymovedown: EnemyArray)
    {
        enemymovedown.Position.y += movedownamount * GetFrameTime();
    }
    MoveCount++;
    if (MoveCount >= DeathMoveCountTrigger)
    {
        printf("PlayerShouldBeDead\n");
    }
}

Texture2D InitSpriteTexture(const char *TextureFilePath)
{
    const Texture2D texture = LoadTexture(TextureFilePath);

    return texture;
}

void DrawSpriteAtlus(const Texture2D &SpriteTexture, const Vector2 SpriteAtlusUVLocation, const Vector2 SpriteAtlusSize,
                     const Vector2 SpritePosition, const Vector2 SpriteScale)
{
    //TODO: Add offsets for each enemy based on col and row
    //DrawTexture(player.PlayerTexture, texture_x, texture_y, WHITE);
    //rect gets start uv location,and then texture height and width
    const Rectangle AtlusUV = {SpriteAtlusUVLocation.x, SpriteAtlusUVLocation.y, SpriteAtlusSize.x, SpriteAtlusSize.y};
    //dest width and height will scale up the sprite
    const Rectangle Dest = {
        SpritePosition.x, SpritePosition.y, AtlusUV.width * SpriteScale.x,
        AtlusUV.height * SpriteScale.x
    };
    //DrawTextureRec(player.PlayerTexture, AtlusUV, Vector2{player.PlayerPos.x,player.PlayerPos.y}, WHITE);
    DrawTexturePro(SpriteTexture, AtlusUV, Dest, Vector2{0, 0}, 0, GREEN);
}
