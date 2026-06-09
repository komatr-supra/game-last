/**
 * @file VehicleTaskMoving.hpp
 * @author your name (you@domain.com)
 * @brief handle vehicle move
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include "Logistic.hpp"
#include "TaskBase.hpp"
#include "raylib.h"
#include "vehicle/tasks/TaskBase.hpp"

// for lerp, returning position
#include "raymath.h"

namespace game::vehicles
{
class TaskMoving : public TaskBase
{
  private:
    game::world::Road* m_road;
    game::world::City* m_startCity;
    game::world::City* m_targetCity;
    float m_positionNor = 0.0f;

    // test
    Vector3 targetPointTEST;
    Vector3 startPointTest;

  public:
    TaskType GetTaskType() override { return TaskType::TaskMoving; }
    TaskMoving(game::world::Road* road,
               game::world::City* startingCity,
               Vector3 pointTEST_end,
               Vector3 pointTest_start);

    bool Update(Vehicle& vehicle, float time) override;
    /*
    {
        float moveNor = (vehicle.GetMaxSpeed() * time) / m_road->lenght;
        m_positionNor += moveNor;

        if (m_positionNor >= 1.0f)
        {
            return true;
        }
        return false;
    }
*/
    void Recalculate();
};
} // namespace game::vehicles