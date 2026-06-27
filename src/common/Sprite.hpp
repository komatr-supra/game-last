/**
 * @file Sprite.hpp
 * @author komatr
 * @brief sprite struct and related functions, main namespace = same acess as raylib functions
 * sprite is an image in texture pack + ORIGIN
 * @date 2026-05-21
 */
#pragma once

#include "raylib.h"

struct Sprite
{
    Texture2D* texture;
    Rectangle sourceRect;
    Vector2 origin;
    Sprite(Texture2D* tex) : texture(tex) {}
};

inline void DrawSprite(const Sprite* sprite, Vector2 position, Vector2 scale = {1.0f, 1.0f}, float rotation = 0, Color tintColor = WHITE)
{
    float destWidth = sprite->sourceRect.width * scale.x;
    float destHeight = sprite->sourceRect.height * scale.y;

    Vector2 scaledOrigin = {sprite->origin.x * scale.x, sprite->origin.y * scale.y};

    Rectangle destRect = {position.x, position.y, destWidth, destHeight};

    DrawTexturePro(*sprite->texture, sprite->sourceRect, destRect, scaledOrigin, rotation, tintColor);
}

inline void DrawSpriteRect(const Sprite& sprite, Rectangle targetRectangle, Color color = WHITE)
{ DrawTexturePro(*sprite.texture, sprite.sourceRect, targetRectangle, {0, 0}, 0, color); }

struct SpriteNP
{
    Texture2D* texture;
    NPatchInfo nPatchInfo;
};

inline void DrawSpriteNP(SpriteNP spriteNP, Rectangle destination, Color tintColor = WHITE)
{ DrawTextureNPatch(*spriteNP.texture, spriteNP.nPatchInfo, destination, {0, 0}, 0, tintColor); }