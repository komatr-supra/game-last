/**
 * @file AssetManager.hpp
 * @author your name (you@domain.com)
 * @brief Load assets, should take care of loading/unloading or prevent multiple or wrong reading,
 *        maybe cooperate with renderer, sound manager, etc...
 *        all sprites are loaded at start
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
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
