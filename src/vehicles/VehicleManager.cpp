
#include "VehicleManager.hpp"

// #include "Core.hpp"
#include "Vehicle.hpp"
#include "core/AssetManager.hpp"
#include "raylib.h"
#include "vehicles/VehicleDefinition.hpp"
#include "world/Logistic.hpp"
#include "world/World.hpp"
#include <string>
#include <vector>

namespace game::vehicles
{

VehicleManager::VehicleManager(game::core::AssetManager& assetManager, game::world::World& world)
    : m_assetManager(assetManager), m_world(world)
{
}
VehicleManager::~VehicleManager() = default;
void VehicleManager::Init() {}

Vehicle* VehicleManager::CreateVehicle(int carID, int cityID)
{
    static size_t vehicleIndex = 0;
    auto car = std::make_unique<Vehicle>(GenerateCarName(), m_assetManager.GetVehicleDefinition(carID));
    Vehicle* vehicle = car.get();
    vehicle->SetPosition(m_world.GetCityByID(cityID)->Position);
    TraceLog(LOG_INFO,
             "car: %s created in: %s, coordination: %d, %d, %d",
             vehicle->GetName().c_str(),
             m_world.GetCityByID(cityID)->Name.c_str(),
             vehicle->GetPosition().x,
             vehicle->GetPosition().y,
             vehicle->GetPosition().z);
    m_vehicles.emplace(vehicleIndex, std::move(car));
    vehicleIndex++;
    return vehicle;
}

void VehicleManager::Update(float deltaTime)
{
    for (const auto& [vehicleIndex, vehicle] : m_vehicles) { vehicle->Update(deltaTime); }
}

void VehicleManager::DrawAllVehicles()
{
    static bool testShow = true;
    for (const auto& [vehicleIndex, vehicle] : m_vehicles)
    {
        if (testShow)
        {
            testShow = false;
            TraceLog(LOG_WARNING, "car mesh count: %d", m_assetManager.GetModel(vehicle->GetTypeData().modelHandle).materialCount);
        }
        DrawModelEx(m_assetManager.GetModel(vehicle->GetTypeData().modelHandle),
                    {vehicle->GetPosition().x, 0.01f, vehicle->GetPosition().z},
                    {0, 1, 0},
                    0.0f,
                    {1.0f, 1.0f, 1.0f},
                    WHITE);
    }
}
std::vector<const VehicleDefinition*> VehicleManager::GetVehicleDatabase() const { return m_assetManager.GetVehicleDatabase(); }
std::string VehicleManager::GenerateCarName() const
{
    static int vehicleCounter = 1;
    return "Vehicle " + std::to_string(vehicleCounter++);
}
std::vector<Vehicle*> VehicleManager::GetVehicles()
{
    std::vector<Vehicle*> view;
    for (auto& [id, vehicle] : m_vehicles) { view.push_back(vehicle.get()); }
    return view;
}
const std::string& VehicleManager::GetVehicleTypeText(game::vehicles::CarType type) const { return m_assetManager.GetTypeText(type); }
} // namespace game::vehicles