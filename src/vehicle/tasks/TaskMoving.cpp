

#include "vehicle/tasks/TaskMoving.hpp"
#include "raylib.h"
#include "raymath.h"
#include "vehicle/Vehicle.hpp"

namespace game::vehicles
{

TaskMoving::TaskMoving(game::world::Road* road,
                       game::world::City* startingCity,
                       Vector3 pointTEST_end,
                       Vector3 pointTEST_start)
    : TaskBase("Task moving"),
      m_road(road),
      m_startCity(startingCity),
      targetPointTEST(pointTEST_end),
      startPointTest(pointTEST_start)
{
}

bool TaskMoving::Update(Vehicle& vehicle, float gameTime)
{
    m_positionNor += gameTime;
    if (m_positionNor < 1.0f)
    {
        TraceLog(LOG_WARNING, "car is moving %.2f", m_positionNor);
        vehicle.SetPosition(Vector3Lerp(startPointTest, targetPointTEST, m_positionNor));
        return true;
    }
    else
    {
        TraceLog(LOG_WARNING, "task moving should stop");
        return false;
    }
}

// TODO: real calculation
void TaskMoving::Recalculate() { m_positionNor = 0; }

} // namespace game::vehicles