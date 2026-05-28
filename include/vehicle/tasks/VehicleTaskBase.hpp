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

class Vehicle;

class VehicleTaskBase
{
  protected:
    const std::string m_taskText;

  public:
    VehicleTaskBase(std::string taskName) : m_taskText(std::move(taskName)) {}

    virtual ~VehicleTaskBase() = default;

    // true = keep this task, false = finished
    [[nodiscard]] virtual bool Update(Vehicle& vehicle, float time) = 0;
    virtual const std::string& GetLocationText() const = 0;
    virtual Vector2 GetPosition() const = 0;
    virtual const std::string& GetTaskText() const = 0;
};
