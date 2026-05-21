#pragma once

#include <string>

class Car;

class VehicleTaskBase
{
  protected:
    Car& m_car;
    std::string m_name;
    const float m_timeToComplete;
    float m_timeElapsed = 0;

  public:
    VehicleTaskBase(Car& car, std::string taskName, float timeToComplete)
        : m_car(car),
          m_name(std::move(taskName)),
          m_timeToComplete(timeToComplete),
          m_timeElapsed(0.0f)
    {
    }

    virtual ~VehicleTaskBase() = default;

    [[nodiscard]] virtual bool Execute(float time) = 0;

    std::string GetName() { return m_name; }
    float GetTimeToComplete() const { return m_timeToComplete; }
    float GetTimeRlapsed() const { return m_timeElapsed; }
};
