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
