/**
 * @file Vehicle.hpp
 * @author komatr
 * @brief vehicle related function, information about trucks load, position, schedule, etc
 * @date 2026-05-21
 */
#pragma once
#include "Task.hpp"
#include "VehicleDefinition.hpp"
#include "raylib.h"

#include <string>

namespace game::vehicles
{

class Vehicle
{
  public:
    enum class TaskType
    {
        NOT_SET,
        Move
    };

  private:
    const std::string m_name;
    Vector3 m_position;
    int m_speedCurrent;
    const VehicleDefinition& m_typeData;
    game::task::TaskManager<Vehicle> m_taskManager;

  public:
    Vehicle(std::string name, const VehicleDefinition& data);
    ~Vehicle();

    void Update(const game::core::Time& gameTime);
    const std::string& GetName() { return m_name; }
    const VehicleDefinition& GetTypeData() const;

    Vector3 GetPosition() { return m_position; }
    void SetPosition(Vector3 position);
};
} // namespace game::vehicles