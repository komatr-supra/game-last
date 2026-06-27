/**
 * @file VehicleManager.hpp
 * @author komatr
 * @brief take care about trucks, buy, sell, find, update them all, etc...
 * @date 21.5.2026
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "ManagerBase.hpp"
#include "VehicleDefinition.hpp"

#include <cstddef>
#include <memory>
#include <unordered_map>
#include <vector>

namespace game
{
namespace core
{
class AssetManager;
} // namespace core
namespace world
{

class World;
}

namespace vehicles
{
class Vehicle;

class VehicleManager : public Manager
{
  private:
    game::core::AssetManager& m_assetManager;
    game::world::World& m_world;
    std::unordered_map<size_t, std::unique_ptr<Vehicle>> m_vehicles;
    std::string GenerateCarName() const;

  public:
    VehicleManager(game::core::AssetManager& assetManager, game::world::World& world);
    ~VehicleManager();
    Vehicle* CreateVehicle(int carID, int cityID);
    void Update(float deltaTime);
    void DrawAllVehicles();
    std::vector<const VehicleDefinition*> GetVehicleDatabase() const;
    void Init() override;
    std::vector<Vehicle*> GetVehicles();
    const std::string& GetVehicleTypeText(game::vehicles::CarType type) const;
};
} // namespace vehicles
} // namespace game