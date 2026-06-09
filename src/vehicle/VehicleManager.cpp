
#include "vehicle/VehicleManager.hpp"
#include "AssetManager.hpp"
#include "raylib.h"
#include "vehicle/Vehicle.hpp"

namespace game::vehicles
{

VehicleManager::VehicleManager(game::assets::AssetManager& assetManager) : m_assetManager(assetManager) {}
VehicleManager::~VehicleManager() = default;
Vehicle* VehicleManager::CreateVehicle(CarType carType)
{
    static size_t vehicleIndex = 0;
    auto car = std::make_unique<Vehicle>("test car name", m_assetManager.GetVehicleDefinition(carType));
    Vehicle* vehicle = car.get();
    m_vehicles.emplace(vehicleIndex, std::move(car));
    vehicleIndex++;
    return vehicle;
}

void VehicleManager::Update(float time)
{
    for (const auto& [vehicleIndex, vehicle] : m_vehicles)
    {
        vehicle->Update(time);
    }
}

void VehicleManager::DrawAllVehicles()
{
    static bool testShow = true;
    for (const auto& [vehicleIndex, vehicle] : m_vehicles)
    {
        // test on UI layer
        // DrawCircle(vehicle->GetPosition().x, vehicle->GetPosition().y, 20, RED);if
        if (testShow)
        {
            testShow = false;
            TraceLog(LOG_WARNING,
                     "car mesh count: %d",
                     m_assetManager.GetModel(vehicle->GetTypeData().modelHandle).materialCount);
        }
        DrawModelEx(m_assetManager.GetModel(vehicle->GetTypeData().modelHandle),
                    {vehicle->GetPosition().x, 0.01f, vehicle->GetPosition().z},
                    {0, 1, 0},
                    vehicle->rotation,
                    {0.1f, 0.1f, 0.1f},
                    WHITE);
    }
}
} // namespace game::vehicles