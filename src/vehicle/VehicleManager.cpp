
#include "vehicle/VehicleManager.hpp"
#include "AssetManager.hpp"
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
    for (const auto& [vehicleIndex, vehicle] : m_vehicles)
    {
        DrawCircle(vehicle->GetPosition().x, vehicle->GetPosition().y, 20, RED);
    }
}
} // namespace game::vehicles