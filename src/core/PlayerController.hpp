/**
 * @file PlayerController.hpp
 * @author komatr
 * @brief input, camera anchor
 * @date 3.7.2026
 */

#pragma once
#include "camera/CameraPlayerAnchor.hpp"
#include "world/WorldObjectBase.hpp"
#include <memory>

namespace game::core
{
class PlayerController
{
  private:
    std::unique_ptr<game::world::WorldObject> m_playerAnchor;

  public:
    PlayerController() : m_playerAnchor(std::make_unique<game::core::CameraPlayerAnchor>({{0, 0, 0}, 1})) {};
    game::world::WorldObject& GetCameraAnchor() { return *m_playerAnchor; }
};
} // namespace game::core