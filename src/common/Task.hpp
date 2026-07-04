/**
 * @file Task.hpp
 * @author komatr
 * @brief task and task manager related stuff, task is the main feature used for
 * every game entity, like: vehicles, cities and roads
 * @date 18.06.2026
 */
#pragma once
#include "core/TimeManager.hpp"
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
    game::GameTime m_startTime;
    game::GameTime m_totalDuration;

  public:
    virtual void Update(T& owner, game::GameTime gameTime) = 0;
    ITask(game::GameTime startTime, game::GameTime duration, T::TaskType task_t)
        : m_startTime(startTime), m_totalDuration(duration), taskType(task_t)
    {
    }
    virtual ~ITask() = default;

    virtual game::GameTime GetExpectedStartTime() const { return m_startTime; }
    virtual game::GameTime GetExpectedEndTime() const { return m_startTime + m_totalDuration; }
};

template <typename T> class TaskManager
{
  private:
    T& m_owner;
    std::vector<std::unique_ptr<task::ITask<T>>> m_tasks;
    game::GameTime m_nextCheck;

  public:
    TaskManager(T& owner) : m_owner(owner), m_nextCheck(0) {}
    virtual ~TaskManager() = default;
    virtual void Update(const game::GameTime& time)
    {
        if (!m_tasks.empty())
            if (time >= m_nextCheck) { m_tasks.front()->Update(m_owner, time); }
    }
};
} // namespace game::task