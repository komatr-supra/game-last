#include "vehicle/tasks/VehicleTaskIdle.hpp"
#include "raylib.h"

namespace game::vehicles
{
VehicleTaskIdle::VehicleTaskIdle(/* args */) : VehicleTaskBase("Idle") {}

VehicleTaskIdle::~VehicleTaskIdle() {}

bool VehicleTaskIdle::Update(Vehicle& vehicle, float time)
{
    TraceLog(LOG_WARNING, "Update of the vehicle: %s\nGame time passed: %f", vehicle.GetName().c_str(), time);
    return true;
}
Vector2 VehicleTaskIdle::GetPosition() const { return {500, 500}; }
} // namespace game::vehicles
