#include "Config.hpp"

#include "vehicle/VehicleDatabase.hpp"
#include "vehicle/VehicleDefinition.hpp"

#include "json.hpp"

#include <fstream>

VehicleDatabase::VehicleDatabase(/* args */)
{
    std::ifstream f(Config::FilePaths::Vehicles);
    nlohmann::json data = nlohmann::json::parse(f);
    for (auto& vehicleJSON : data["vehicles"])
    {
        m_vehicleDatabase.emplace_back(
            std::make_unique<VehicleDefinition>(vehicleJSON["internalName"].get<std::string>(),
                                                vehicleJSON["type"].get<std::string>(),
                                                vehicleJSON["maxSpeed"].get<int>(),
                                                vehicleJSON["maxCapacity"].get<int>(),
                                                vehicleJSON["price"].get<int>(),
                                                vehicleJSON["spriteName"].get<std::string>()));
    }
}

VehicleDatabase::~VehicleDatabase() {}