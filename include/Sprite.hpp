/**
 * @file Sprite.hpp
 * @author your name (you@domain.com)
 * @brief sprite is an image in texture pack, GOT ORIGIN
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include "raylib.h"

#include <string>

struct Sprite
{
    std::string name;
    Texture2D texture;
    Rectangle sourceRect;
    Vector2 origin;
};

inline void DrawSprite(const Sprite& sprite,
                       Vector2 position,
                       Vector2 scale = {1.0f, 1.0f},
                       float rotation = 0,
                       Color tintColor = WHITE)
{
    float destWidth = sprite.sourceRect.width * scale.x;
    float destHeight = sprite.sourceRect.height * scale.y;

    Vector2 scaledOrigin = {sprite.origin.x * scale.x, sprite.origin.y * scale.y};

    Rectangle destRect = {position.x, position.y, destWidth, destHeight};

    DrawTexturePro(sprite.texture, sprite.sourceRect, destRect, scaledOrigin, rotation, tintColor);
}

inline void DrawSpriteRect(const Sprite& sprite, Rectangle targetRectangle, Color color = WHITE)
{
    DrawTexturePro(sprite.texture, sprite.sourceRect, targetRectangle, {0, 0}, 0, color);
}

struct Sprite9Slice
{
    std::string name;
    Texture2D texture;
    NPatchInfo nPatchInfo;
};

inline void DrawSpriteNP(Sprite9Slice sprite, Rectangle destination, Color tintColor = WHITE)
{
    DrawTextureNPatch(sprite.texture, sprite.nPatchInfo, destination, {0, 0}, 0, tintColor);
}
