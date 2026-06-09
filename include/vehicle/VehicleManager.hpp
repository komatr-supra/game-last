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

#include "vehicle/VehicleDefinition.hpp"
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <vector>

namespace game::assets
{
class AssetManager;
}

namespace game::vehicles
{

class Vehicle;

class VehicleManager
{
  private:
    game::assets::AssetManager& m_assetManager;

    std::unordered_map<size_t, std::unique_ptr<Vehicle>> m_vehicles;

  public:
    VehicleManager(game::assets::AssetManager& assetManager);
    ~VehicleManager();
    Vehicle* CreateVehicle(CarType carType);
    void Update(float time);
    void DrawAllVehicles();

    std::vector<VehicleDefinition*> GetVehicleDatabase() const;

    // const std::vector<std::unique_ptr<Vehicle>>& GetAllVehicles() const { return m_vehicles; }
};
} // namespace game::vehicles