#pragma once

#include "VehicleTaskBase.hpp"

namespace game::vehicles
{

class VehicleTaskIdle : public VehicleTaskBase
{
  private:
    /* data */
  public:
    VehicleTaskIdle(/* args */);
    ~VehicleTaskIdle();

    bool Update(Vehicle& vehicle, float time) override;
    Vector2 GetPosition() const override;
};
} // namespace game::vehicles