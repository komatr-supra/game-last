#include "vehicle/VehicleManager.hpp"
#include "core/AssetManager.hpp"
#include "vehicle/Vehicle.hpp"

VehicleManager::VehicleManager(AssetManager& assetManager) : m_assetManager(assetManager) {}

VehicleManager::~VehicleManager() {}

void VehicleManager::CreateVehicle(City* startingCity) {}

void VehicleManager::Update(float time)
{
    for (auto& vehicle : m_vehicles)
    {
        vehicle->Update(time);
    }
}

void VehicleManager::DrawAllVehicles()
{
    for (auto& vehicle : m_vehicles)
    {
    }
}