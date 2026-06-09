#include "vehicle/Vehicle.hpp"

#include "raylib.h"

namespace game::vehicles
{

Vehicle::Vehicle(std::string name, const VehicleDefinition& data) : m_name(std::move(name)), m_data(data) {}

Vehicle::~Vehicle() {}

void Vehicle::Update(float time) { TraceLog(LOG_INFO, "vehicle update"); }

const game::vehicles::VehicleDefinition& Vehicle::GetTypeData() const { return m_data; }
Vector2 Vehicle::GetPosition() { return {300, 300}; }
} // namespace game::vehicles