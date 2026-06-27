#pragma once
#include "ManagerBase.hpp"
#include "gui/GuiFleet.hpp"

// TODO: add other windows as separate files
namespace game
{
namespace graphics
{
class GameCamera;
}
namespace vehicles
{
class VehicleManager;
}
} // namespace game

namespace game::gui
{
class GuiManager : public Manager
{
  private:
    game::vehicles::VehicleManager& m_vm;
    game::graphics::GameCamera& m_cam;

    GuiFleet m_fleetWindiow;

  public:
    GuiManager(game::vehicles::VehicleManager& vehicleManager, game::graphics::GameCamera& gameCamera)
        : m_vm(vehicleManager), m_cam(gameCamera), m_fleetWindiow(vehicleManager, gameCamera)
    {
    }
    void Draw();
    void Init() override;
};

} // namespace game::gui