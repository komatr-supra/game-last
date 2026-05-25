/**
 * @file VehicleTaskBase.hpp
 * @author your name (you@domain.com)
 * @brief base class for all vehicle action - each action got separated file
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <string>

// for test TODO FIX - returning a position
#include "raylib.h"

enum class TaskType
{
    WAITING,
    MOVING,
    LOADING,
    UNLOADING
};

class Vehicle;

class VehicleTaskBase
{
  protected:
    Vehicle& m_vehicle;
    TaskType m_taskType;
    std::string m_nameUI;

  public:
    VehicleTaskBase(Vehicle& vehicle, std::string taskName) : m_vehicle(vehicle), m_nameUI(std::move(taskName)) {}

    virtual ~VehicleTaskBase() = default;

    [[nodiscard]] virtual bool Execute(float time) = 0;

    const std::string& GetName() const { return m_nameUI; }
    virtual Vector2 GetPosition() const = 0;
};
