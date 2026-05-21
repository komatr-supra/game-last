#pragma once

#include "raylib.h"
#include "raymath.h"

#include <algorithm>
#include <memory>
#include <vector>

class AssetManager;
class Vehicle;
struct City;

class VehicleManager
{
  private:
    AssetManager& m_assetManager;
    std::vector<std::unique_ptr<Vehicle>> m_vehicles;

  public:
    VehicleManager(AssetManager& assetManager);
    ~VehicleManager();

    void CreateVehicle(City* startingCity);
    void Update(float time);
    void DrawAllVehicles();
};
