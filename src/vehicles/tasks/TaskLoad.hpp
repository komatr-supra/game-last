/**
 * @file TaskLoad.hpp
 * @author komatr
 * @brief handle cargo load for vehicle
 * @date 17.06.2026
 */
#pragma once
#include "Core.hpp"
#include "vehicles/Vehicle.hpp"

namespace game::vehicles
{
class TaskLoad : public game::task::ITask<Vehicle>
{
  public:
    TaskLoad(game::core::Time(startTime), game::core::Time(duration))
        : game::task::ITask<Vehicle>(startTime, duration, Vehicle::TaskType::Move)
    {
    }
};
} // namespace game::vehicles