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

class VehicleManager
{
    using Am = game::core::AssetManager;

  private:
    Am& m_assetManager;
    std::unordered_map<size_t, std::unique_ptr<Vehicle>> m_vehicles;

  public:
    VehicleManager(Am& assetManager);
    ~VehicleManager();
    Vehicle* CreateVehicle(CarType carType);
    void Update(game::core::Time time);
    void DrawAllVehicles();
    std::vector<VehicleDefinition*> GetVehicleDatabase() const;
};
} // namespace game::vehicles