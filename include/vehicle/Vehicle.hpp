/**
 * @file Vehicle.hpp
 * @author your name (you@domain.com)
 * @brief vehicle related function, information about trucks load, position, schedule, etc
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include "raylib.h"
#include "vehicle/VehicleDefinition.hpp"
#include "vehicle/tasks/TaskBase.hpp"

#include <memory>
#include <string>
#include <vector>

namespace game::vehicles
{

class Vehicle
{
  private:
    const std::string m_name;
    Vector3 m_position;
    int m_speedCurrent;
    const VehicleDefinition& m_typeData;
    std::vector<std::unique_ptr<TaskBase>> m_tasks;

  public:
    Vehicle(std::string name, const VehicleDefinition& data);
    ~Vehicle();

    void Update(float time);
    const std::string& GetName() { return m_name; }
    const VehicleDefinition& GetTypeData() const;

    void AddTask(std::unique_ptr<TaskBase> task);
    Vector3 GetPosition() { return m_position; }
    void SetPosition(Vector3 position);

    // TODO: real function this is a TEST!!!
    Vector3 target;
    void SetTargetPos(Vector3 position) { target = position; }
    float rotation = 0;
};
} // namespace game::vehicles