#pragma once
#include "ManagerBase.hpp"
namespace game::vehicles
{
class VehicleManager;
}

namespace game::gui
{
class GuiFleet : public NonCopyable
{
  private:
    game::vehicles::VehicleManager& m_vehicleManager;

  public:
    GuiFleet(game::vehicles::VehicleManager& vehicleManager);
    void Draw();
};
} // namespace game::gui