#pragma once
#include "ManagerBase.hpp"
#include "gui/GuiFleet.hpp"

namespace game::vehicles
{
class VehicleManager;
}

namespace game::gui
{
class GuiManager : public Manager
{
  private:
    game::vehicles::VehicleManager& vm;
    GuiFleet m_fleetWindiow;

  public:
    GuiManager(game::vehicles::VehicleManager& vehicleManager) : vm(vehicleManager), m_fleetWindiow(vehicleManager) {}
    void Draw();
    void Init() override;
};

} // namespace game::gui