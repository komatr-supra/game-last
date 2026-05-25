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
#include "raylib.h"

#include <algorithm>
#include <memory>
#include <vector>

class AssetManager;
class Vehicle;
struct City;
struct VehicleDefinition;

class VehicleManager
{
  private:
    AssetManager& m_assetManager;
    std::vector<std::unique_ptr<VehicleDefinition>> m_vehicleDatabase;
    std::vector<std::unique_ptr<Vehicle>> m_vehicles;

  public:
    VehicleManager(AssetManager& assetManager);
    ~VehicleManager();

    Vehicle* CreateVehicle(City* startingCity, const std::string& type); // todo add owner
    void Update(float time);
    void DrawAllVehicles();

    std::vector<VehicleDefinition*> GetVehicleDatabase() const;

    const std::vector<std::unique_ptr<Vehicle>>& GetAllVehicles() const { return m_vehicles; }
};
