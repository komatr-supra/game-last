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

enum class CarType
{
    NOT_SET,
    Pickup,
    Van,
    Truck,
    LAST
};

struct VehicleDefinition
{
    CarType type;
    int speedMax;
    int capacityMax;
    int price;
    Texture2D* texture;

    VehicleDefinition(CarType type, int maxSpeed, int capacity, int cost, Texture2D* tex)
        : type(type), speedMax(maxSpeed), capacityMax(capacity), price(cost), texture(texture)
    {
    }
};

class Vehicle
{
  private:
    const std::string m_name;
    int m_speedCurrent;
    VehicleDefinition& m_data;
    std::vector<std::unique_ptr<VehicleTaskBase>> m_tasks;
    std::vector<ShipmentItem*> m_cargo;

  public:
    Vehicle(std::string name, VehicleDefinition& data, City* city);
    ~Vehicle();

    void Update(float time);

    const std::string& GetName() const;
    const VehicleDefinition& GetTypeData() const;
    int GetMaxSpeed() const;
    int GetMaxCapacity() const;
    int GetPrice() const;
    const Texture2D& GetTexture() const;
    Vector2 GetPosition();

    void AddTask(std::unique_ptr<VehicleTaskBase> task);
};