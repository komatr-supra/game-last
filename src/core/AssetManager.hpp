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

#include "entities/vehicles/VehicleDefinition.hpp"
#include "graphics/Sprite.hpp"

#include "raylib.h"

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace game::entities::vehicles
{
struct VehicleDefinition;
}

namespace game::core
{
class AssetManager
{
    using Vd = game::entities::vehicles::VehicleDefinition;

  private:
    const char* fallback = "default";
    // collections for assets
    std::unordered_map<std::string, Texture2D> m_textures;
    std::unordered_map<std::string, Sprite> m_sprites;
    std::unordered_map<std::string, SpriteNP> m_spritesNP;
    std::unordered_map<std::string, size_t> m_nameToModelID;
    std::vector<Model> m_models;

    std::unordered_map<game::entities::vehicles::CarType, std::unique_ptr<Vd>> m_vehicleDatabase;
    Font m_font;

    game::entities::vehicles::CarType GetCarType(const std::string& carName) const;

  public:
    AssetManager();
    ~AssetManager();

    /// @brief Return a Sprite Reference.
    /// @param spriteName string from "texturepack.hpp"
    /// @return
    const Texture2D& GetTexture(const std::string& textureName) const;
    const Sprite& GetSprite(const std::string& spriteName) const;
    const SpriteNP& GetSpriteNP(const std::string& spriteName) const;
    size_t GetOrCreateModelID(const std::string& modelName);
    const Model& GetModel(size_t) const;
    const Model& GetModel(const std::string& modelName) const;
    std::vector<const Vd*> GetVehicleDatabase() const;
    const Vd& GetVehicleDefinition(game::entities::vehicles::CarType carType);
    const Font& GetFont() const;
};
} // namespace game::core