#pragma once

#include "vehicle/tasks/VehicleTaskBase.hpp"

class VehicleTaskIdle : public VehicleTaskBase
{
  private:
    /* data */
  public:
    VehicleTaskIdle(/* args */);
    ~VehicleTaskIdle();

    bool Update(Vehicle& vehicle, float time) override;
    const std::string& GetLocationText() const override;
    Vector2 GetPosition() const override;
    const std::string& GetTaskText() const override;
};

VehicleTaskIdle::VehicleTaskIdle(/* args */) : VehicleTaskBase("Idle") {}

VehicleTaskIdle::~VehicleTaskIdle() {}

bool VehicleTaskIdle::Update(Vehicle& vehicle, float time) {}
const std::string& VehicleTaskIdle::GetLocationText() const {}
Vector2 VehicleTaskIdle::GetPosition() const {}
const std::string& VehicleTaskIdle::GetTaskText() const {}
