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

struct VehicleDefinition
{
    std::string nameInternal;
    std::string nameType;
    int speedMax;
    int capacityMax;
    int price;
    std::string texturePath;

    VehicleDefinition(std::string internal, std::string type, int speed, int cap, int p, std::string tex)
        : nameInternal(std::move(internal)),
          nameType(std::move(type)),
          speedMax(speed),
          capacityMax(cap),
          price(p),
          texturePath(std::move(tex))
    {
    }
};

class Vehicle
{
  private:
    const std::string m_name;
    int m_speedCurrent;
    VehicleDefinition* m_data;
    City* m_city; // last city, where this vehicle was
    std::vector<std::unique_ptr<VehicleTaskBase>> m_tasks;
    std::vector<ShipmentItem*> m_cargo;

  public:
    Vehicle(std::string name, VehicleDefinition* data, City* city);
    ~Vehicle();

    void Update(float time);

    const std::string& GetName() const;
    const std::string& GetTypeName() const;
    City* GetLastCity() const { return m_city; }
    const std::string& GetInternalName() const;
    int GetMaxSpeed() const;
    int GetMaxCapacity() const;
    int GetPrice() const;
    const std::string& GetTexturePath() const;
    Vector2 GetPosition();

    void SetLastCity(City* city) { m_city = city; }
    void AddTask(std::unique_ptr<VehicleTaskBase> task);
};