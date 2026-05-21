#pragma once

#include "Sprite.hpp"

#include "raylib.h"

#include <string>
#include <unordered_map>

class AssetManager
{
  private:
    Texture2D m_texture;
    std::unordered_map<std::string, Sprite> m_sprites;

  public:
    AssetManager(/* args */);
    ~AssetManager();

    Sprite GetSprite(const std::string& spriteName);
};
