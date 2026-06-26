/**
 * @file AssetManager.hpp
 * @author your name (you@domain.com)
 * @brief Load assets, should take care of loading/unloading or prevent multiple or wrong reading,
 *        maybe cooperate with renderer, sound manager, etc...
 *        all sprites are loaded at start
 * @date 2026-05-21
 */
#pragma once

#include "ManagerBase.hpp"
#include "Sprite.hpp"
#include "vehicles/VehicleDefinition.hpp"

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
class AssetManager : public Manager
{
    using Vd = game::vehicles::VehicleDefinition;

  private:
    static inline constexpr const char* fallback = "default";
    // collections for assets
    std::unordered_map<std::string, Texture2D> m_textures;
    std::unordered_map<std::string, Sprite> m_sprites;
    std::unordered_map<std::string, SpriteNP> m_spritesNP;
    std::unordered_map<std::string, size_t> m_nameToModelID;
    std::vector<Model> m_models;

    std::vector<std::unique_ptr<Vd>> m_vehicleDatabase;
    Font m_font;

    game::vehicles::CarType GetCarType(const std::string& carName) const;
    const std::unordered_map<std::string, game::vehicles::CarType> conversionMap = {{"Pickup", game::vehicles::CarType::Pickup},
                                                                                    {"Van", game::vehicles::CarType::Van},
                                                                                    {"Truck", game::vehicles::CarType::Truck}};

  public:
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
    const Vd& GetVehicleDefinition(int carID);
    const Font& GetFont() const;
    const std::string& GetTypeText(game::vehicles::CarType type) const;
    void Init() override;
    void Shut() override;
};
} // namespace game::core