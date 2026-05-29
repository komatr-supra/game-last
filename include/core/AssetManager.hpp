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
    // backup sprites TODO: delete at the end
    Texture2D m_errorTexture;
    Sprite m_errorSprite;
    SpriteNP m_errorSpriteNP;

    // collections for assets
    std::unordered_map<std::string, Texture2D> m_textures;
    std::unordered_map<std::string, Sprite> m_sprites;
    std::unordered_map<std::string, SpriteNP> m_spritesNP;
    Font m_font;

  public:
    AssetManager();
    ~AssetManager();

    /// @brief Return a Sprite Reference.
    /// @param spriteName string from "texturepack.hpp"
    /// @return
    const Sprite& GetSprite(const std::string& spriteName);
    const SpriteNP& GetSpriteNP(const std::string& spriteName);
    Font GetFont();
};
