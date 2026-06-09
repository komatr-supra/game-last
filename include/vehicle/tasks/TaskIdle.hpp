#pragma once

#include "TaskBase.hpp"

namespace game::world
{
struct City;
}

namespace game::vehicles
{

class TaskIdle : public TaskBase
{
  private:
    float m_elapsedTime;
    game::world::City* m_city;

  public:
    TaskType GetTaskType() override { return TaskType::TaskIdle; }
    TaskIdle(game::world::City* city);
    ~TaskIdle();

    bool Update(Vehicle& vehicle, float time) override;
};
} // namespace game::vehicles