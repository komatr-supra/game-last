/**
 * @file VehicleManager.hpp
 * @author your name (you@domain.com)
 * @brief take care about trucks, buy, sell, find, update them all, etc...
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include "Core.hpp"
#include "VehicleDefinition.hpp"
#include "world/World.hpp"

#include <cstddef>
#include <memory>
#include <unordered_map>
#include <vector>

namespace game::core
{
class AssetManager;
}

namespace game::vehicles
{
class Vehicle;

class VehicleManager : public game::core::Manager
{
    using Am = game::core::AssetManager;

  private:
    Am& m_assetManager;
    game::world::World& m_world;
    std::unordered_map<size_t, std::unique_ptr<Vehicle>> m_vehicles;
    const char* GenerateCarName() const;

  public:
    VehicleManager(Am& assetManager, game::world::World& world);
    ~VehicleManager();
    Vehicle* CreateVehicle(int carID, int cityID);
    void Update(game::core::Time time);
    void DrawAllVehicles();
    std::vector<const VehicleDefinition*> GetVehicleDatabase() const;
    void Init() override;
    std::vector<Vehicle*> GetVehicles();
    const std::string& GetVehicleTypeText(game::vehicles::CarType type) const;
};
} // namespace game::vehicles