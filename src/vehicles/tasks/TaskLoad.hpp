/**
 * @file TaskLoad.hpp
 * @author your name (you@domain.com)
 * @brief handle vehicle move
 * @version 0.1
 * @date 2026-06-17
 *
 * @copyright Copyright (c) 2026
 *
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