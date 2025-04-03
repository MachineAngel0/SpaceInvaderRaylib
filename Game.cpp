//
// Created by Adams Humbert on 4/1/2025.
//

#include "Game.h"

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

void DrawProjectile(const Projectile &projectile)
{

    //DrawTextureRec(player.PlayerTexture, AtlusUV, Vector2{player.PlayerPos.x,player.PlayerPos.y}, WHITE);
    DrawRectangle(projectile.Position.x,projectile.Position.y,projectile.Size.x,projectile.Size.y, GREEN);

}
