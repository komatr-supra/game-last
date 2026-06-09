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
#include "vehicle/VehicleDefinition.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace game::assets
{
class AssetManager
{
  private:
    const char* fallback = "default";
    // collections for assets
    std::unordered_map<std::string, Texture2D> m_textures;
    std::unordered_map<std::string, Sprite> m_sprites;
    std::unordered_map<std::string, SpriteNP> m_spritesNP;
    std::unordered_map<std::string, size_t> m_nameToModelID;
    std::vector<Model> m_models;

    std::unordered_map<game::vehicles::CarType, std::unique_ptr<game::vehicles::VehicleDefinition>> m_vehicleDatabase;
    Font m_font;

    game::vehicles::CarType GetCarType(const std::string& carName) const
    {
        static const std::unordered_map<std::string, game::vehicles::CarType> conversionMap = {
            {"pickup", game::vehicles::CarType::Pickup},
            {"van", game::vehicles::CarType::Van},
            {"truck", game::vehicles::CarType::Truck}};

        auto it = conversionMap.find(carName);
        if (it != conversionMap.end())
        {
            return it->second;
        }

        return game::vehicles::CarType::NOT_SET;
    }

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
    std::vector<const game::vehicles::VehicleDefinition*> GetVehicleDatabase() const;
    const game::vehicles::VehicleDefinition& GetVehicleDefinition(game::vehicles::CarType carType)
    {
        auto it = m_vehicleDatabase.find(carType);
        if (it != m_vehicleDatabase.end())
            return *it->second.get();
        return *m_vehicleDatabase.at(game::vehicles::CarType::NOT_SET);
    }
    const Font& GetFont() const;
};
} // namespace game::assets