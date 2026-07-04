#include "Vehicle.hpp"

#include "TimeContext.hpp"
#include "raylib.h"

namespace game::vehicles
{

Vehicle::Vehicle(std::string name, const VehicleDefinition& data) : m_name(std::move(name)), m_typeData(data), m_taskManager(*this)
{
    // m_tasks.push_back(std::make_unique<TaskIdle>());
}
Vehicle::~Vehicle() {}

void Vehicle::Update(TimeContext time) {}
const game::vehicles::VehicleDefinition& Vehicle::GetTypeData() const { return m_typeData; }

void Vehicle::SetPosition(Vector3 position) { m_position = {position.x, 0.1f, position.z}; }
} // namespace game::vehicles