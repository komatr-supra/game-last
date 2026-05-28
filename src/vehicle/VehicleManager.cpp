#include "Config.hpp"

#include "core/AssetManager.hpp"
#include "vehicle/Vehicle.hpp"
#include "vehicle/VehicleManager.hpp"

#include "json.hpp"

#include <fstream>

VehicleManager::VehicleManager(AssetManager& assetManager) : m_assetManager(assetManager)
{
    std::ifstream f(game::config::path::VehicleDatabase);
    nlohmann::json data = nlohmann::json::parse(f);
    for (auto& vehicleJSON : data["vehicles"])
    {
        // get texture

        m_vehicleDatabase.emplace_back(std::make_unique<VehicleDefinition>(vehicleJSON["name"].get<std::string>(),
                                                                           vehicleJSON["type"].get<std::string>(),
                                                                           vehicleJSON["maxSpeed"].get<int>(),
                                                                           vehicleJSON["maxCapacity"].get<int>(),
                                                                           vehicleJSON["price"].get<int>(),
                                                                           vehicleJSON["img"].get<std::string>()));
        TraceLog(LOG_ERROR, "auto vytvoreno");
    }
}

VehicleManager::~VehicleManager() {}

std::vector<VehicleDefinition*> VehicleManager::GetVehicleDatabase() const
{
    std::vector<VehicleDefinition*> view;

    for (const auto& vehicleUniqePointer : m_vehicleDatabase)
    {
        view.push_back(vehicleUniqePointer.get());
    }
    TraceLog(LOG_ERROR, "vracim databazi aut o velikosti: %d", view.size());
    return view;
}

Vehicle* VehicleManager::CreateVehicle(City* startingCity, const std::string& type)
{
    auto it = std::find_if(m_vehicleDatabase.begin(),
                           m_vehicleDatabase.end(),
                           [&type](const std::unique_ptr<VehicleDefinition>& v) { return v->nameType == type; });
    if (it != m_vehicleDatabase.end())
    {
        auto newVehicle = std::make_unique<Vehicle>("debilni auto", it->get(), startingCity);

        Vehicle* ptr = newVehicle.get();
        // create vehicle
        m_vehicles.push_back(std::move(newVehicle));
        TraceLog(LOG_ERROR, "car created");
        return ptr;
    }
    return nullptr;
}

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
        DrawCircle(vehicle->GetPosition().x, vehicle->GetPosition().y, 20, RED);
    }
}
