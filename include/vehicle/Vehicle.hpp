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

#include <string>

namespace game::vehicles
{

class Vehicle
{
  private:
    const std::string m_name;
    int m_speedCurrent;
    const VehicleDefinition& m_data;
    // std::vector<std::unique_ptr<VehicleTaskBase>> m_tasks;

  public:
    Vehicle(std::string name, const VehicleDefinition& data);
    ~Vehicle();

    void Update(float time);
    const std::string& GetName() { return m_name; }
    const VehicleDefinition& GetTypeData() const;
    Vector2 GetPosition();

    // void AddTask(std::unique_ptr<VehicleTaskBase> task);
};
} // namespace game::vehicles