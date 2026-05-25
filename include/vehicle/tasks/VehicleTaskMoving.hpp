/**
 * @file VehicleTaskMoving.hpp
 * @author your name (you@domain.com)
 * @brief handle vehicle move
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include "VehicleTaskBase.hpp"
#include "core/Logistic.hpp"
#include "vehicle/Vehicle.hpp"

// for lerp, returning position
#include "raymath.h"

class VehicleTaskMoving : public VehicleTaskBase
{
  private:
    Road* m_road;
    City* m_start;
    City* m_target;
    float m_positionNor = 0.0f;

  public:
    VehicleTaskMoving(Road* road, Vehicle& vehicle, std::string taskName)
        : VehicleTaskBase(vehicle, taskName), m_road(road)
    {
        m_start = vehicle.GetLastCity();
        m_target = m_road->cityA == m_start ? m_road->cityB : m_road->cityA;
    }

    bool Execute(float time) override
    {
        float moveNor = (m_vehicle.GetMaxSpeed() * time) / m_road->lenght;
        m_positionNor += moveNor;

        if (m_positionNor >= 1.0f)
        {
            m_vehicle.SetLastCity(m_target);
            return true;
        }
        return false;
    }

    Vector2 GetPosition() const override { return Vector2Lerp(m_start->Position, m_target->Position, m_positionNor); }
};
