#include "vehicle/tasks/TaskIdle.hpp"
#include "Logistic.hpp"
#include "raylib.h"
#include "vehicle/Vehicle.hpp"

namespace game::vehicles
{
TaskIdle::TaskIdle(game::world::City* city) : TaskBase("Idle"), m_elapsedTime(0), m_city(city) {}

TaskIdle::~TaskIdle() {}

bool TaskIdle::Update(Vehicle& vehicle, float time)
{
    // vehicle.SetPosition(m_city->Position)
    m_elapsedTime += time;
    // TraceLog(LOG_WARNING, "do nothing %.2f", m_elapsedTime);
    return true;
}
} // namespace game::vehicles
