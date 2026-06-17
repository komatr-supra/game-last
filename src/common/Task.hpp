#pragma once

#include "Core.hpp"

#include <memory>
#include <vector>

namespace game::task
{
template <typename T> class ITask
{
  public:
    using Type = typename T::TaskType;
    const Type taskType;

  protected:
    game::core::Time m_startTime;
    game::core::Time m_totalDuration;

  public:
    virtual void Update(T& owner, game::core::Time gameTime) = 0;
    ITask(game::core::Time startTime, game::core::Time duration, T::TaskType task_t)
        : m_startTime(startTime), m_totalDuration(duration), taskType(task_t)
    {
    }
    virtual ~ITask() = default;

    virtual game::core::Time GetExpectedStartTime() const { return m_startTime; }
    virtual game::core::Time GetExpectedEndTime() const { return m_startTime + m_totalDuration; }
};

template <typename T> class TaskManager
{
  private:
    T& m_owner;
    std::vector<std::unique_ptr<task::ITask<T>>> m_tasks;
    game::core::Time m_nextCheck;

  public:
    TaskManager(T& owner) : m_owner(owner), m_nextCheck(0) {}
    virtual ~TaskManager() = default;
    virtual void Update(const game::core::Time& time)
    {
        if (!m_tasks.empty())
            if (time >= m_nextCheck) { m_tasks.front()->Update(m_owner, time); }
    }
};
} // namespace game::task