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
    City* m_startCity;
    City* m_targetCity;
    float m_positionNor = 0.0f;

  public:
    VehicleTaskMoving(std::string taskName, Road* road, City* startingCity) : VehicleTaskBase(taskName), m_road(road)
    {
        m_startCity = startingCity;
        m_targetCity = m_road->cityA == m_startCity ? m_road->cityB : m_road->cityA;
    }

    bool Update(Vehicle& vehicle, float time) override
    {
        float moveNor = (vehicle.GetMaxSpeed() * time) / m_road->lenght;
        m_positionNor += moveNor;

        if (m_positionNor >= 1.0f)
        {
            return true;
        }
        return false;
    }

    Vector2 GetPosition() const override
    {
        return Vector2Lerp(m_startCity->Position, m_targetCity->Position, m_positionNor);
    }
};
