#include <iostream>
#include "raylib.h"
#include "Game.h"

#define ScreenWidth (800)
#define ScreenHeight (450)

#define Window_Title "Space Invaders"

int main(void)
{
    InitWindow(ScreenWidth, ScreenHeight, Window_Title);

    SetTargetFPS(60);

    Texture2D texture = LoadTexture("Assets/SpaceInvaders_SpriteSheet.png");
    const int texture_x = ScreenWidth / 2 - texture.width / 2;
    const int texture_y = ScreenHeight / 2 - texture.height / 2;

    //init player
    Player player = DefaultPlayerstate;
    // set actual values
    player.PlayerPos = Vector2(ScreenWidth / 2, ScreenHeight / 2);
    player.PlayerTexture = texture;

    //loop
    while (!WindowShouldClose())
    {
        // update loop

        //Player Movement keys
        // TODO: Check for out of bounds
        if (IsKeyDown(KEY_D))
        {
            player.PlayerPos.x += player.PlayerSpeed * GetFrameTime();
        }
        if (IsKeyDown(KEY_A))
        {
            player.PlayerPos.x -= player.PlayerSpeed * GetFrameTime();
        }

        // draw
        BeginDrawing();
        ClearBackground(BLACK);
        //DrawTexture(player.PlayerTexture, texture_x, texture_y, WHITE);
        //rect gets start uv location,and then texture height and width
        Rectangle AtlusUV = {0, 0, 17, 10};
        //dest width and height will scale up the sprite
        Rectangle Dest = {player.PlayerPos.x , player.PlayerPos.y, AtlusUV.width *2 , AtlusUV.height*2};
        //DrawTextureRec(player.PlayerTexture, AtlusUV, Vector2{player.PlayerPos.x,player.PlayerPos.y}, WHITE);
        DrawTexturePro(player.PlayerTexture, AtlusUV, Dest, Vector2{0, 0}, 0, GREEN);
        // this gets drawn on top
        DrawText("Hello World!", ScreenWidth / 2 - 50, ScreenHeight / 2, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
