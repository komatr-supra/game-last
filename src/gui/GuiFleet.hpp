#pragma once
#include "ManagerBase.hpp"
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
class GuiFleet : public NonCopyable
{
  private:
    game::vehicles::VehicleManager& m_vehicleManager;
    game::graphics::GameCamera& m_cam;

  public:
    GuiFleet(game::vehicles::VehicleManager& vehicleManager, game::graphics::GameCamera& camera);
    void Draw();
};
} // namespace game::gui