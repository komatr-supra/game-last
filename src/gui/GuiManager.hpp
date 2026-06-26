#pragma once
#include "ManagerBase.hpp"

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

  public:
    GuiManager(game::vehicles::VehicleManager& vehicleManager) : vm(vehicleManager) {}
    void Draw();
    void Init() override;
};

} // namespace game::gui