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
#include "raymath.h"

#include <memory>
#include <string>
#include <vector>

class VehicleTaskBase;
struct ShipmentItem;
struct City;
struct Road;
struct VehicleDefinition;

enum class VEHICLE_STATE
{
    IDLE,
    MOVING,
    LOADING,
    UNLOADING
};

class Vehicle
{
  private:
    const std::string m_name;
    VEHICLE_STATE m_state;
    int m_speedCurrent;
    VehicleDefinition* m_data;
    City* m_city; // last city, where this vehicle was
    std::vector<std::unique_ptr<VehicleTaskBase>> m_tasks;
    std::vector<ShipmentItem*> m_cargo;

  public:
    Vehicle(std::string name, VehicleDefinition* data);
    ~Vehicle();

    const std::string& GetName() const;
    const std::string& GetTypeName() const;
    const std::string& GetInternalName() const;
    int GetMaxSpeed();
    int GetMaxCapacity();
    int GetPrice();
    const std::string& GetTexturePath() const;

    Vector2 GetPosition();

    void Update(float time);
};