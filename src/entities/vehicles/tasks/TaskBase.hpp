/**
 * @file VehicleTaskBase.hpp
 * @author your name (you@domain.com)
 * @brief base class for all vehicle action - each action got separated file
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include <string>

namespace game::entities::vehicles
{
class Vehicle;

enum class TaskType
{
    NotAnyType,
    TaskIdle,
    TaskMoving
};

class TaskBase
{
  protected:
    const std::string m_taskName;

  public:
    virtual TaskType GetTaskType() = 0;

    TaskBase(std::string taskName) : m_taskName(std::move(taskName)) {}
    virtual ~TaskBase() = default;

    // true = keep this task, false = finished
    /**
     * @brief
     *
     * @param vehicle owner of the task
     * @param time gameTime
     * @return true continue this task
     * @return false don't continue -> this task ended
     */
    [[nodiscard]] virtual bool Update(Vehicle& vehicle, float time) = 0;

    const std::string& GetName() { return m_taskName; }
};
} // namespace game::entities::vehicles