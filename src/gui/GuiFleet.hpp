/**
 * @file GuiFleet.hpp
 * @author komatr
 * @brief fleet window = control vehicles and their state/status
 * @date 28.6.2026
 */
#pragma once
#include "NonCopyable.hpp"
namespace game
{
namespace camera
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
    game::camera::GameCamera& m_cam;

  public:
    GuiFleet(game::vehicles::VehicleManager& vehicleManager, game::camera::GameCamera& camera);
    void Draw();
};
} // namespace game::gui