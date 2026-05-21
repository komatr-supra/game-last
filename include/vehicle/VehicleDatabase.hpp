/**
 * @file VehicleDatabase.hpp
 * @author your name (you@domain.com)
 * @brief information about all cars loaded from JSON file with vehicles
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <memory>
#include <vector>

struct VehicleDefinition;

class VehicleDatabase
{
  private:
    std::vector<std::unique_ptr<VehicleDefinition>> m_vehicleDatabase;

  public:
    VehicleDatabase(/* args */);
    ~VehicleDatabase();
};
