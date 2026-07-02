/**
 * @file Camera.hpp
 * @author komatr
 * @brief setup camera (effects, zoom, shaders, etc...)
 * just a simple offset, following "Camera Anchor" => anchor make a tween and position calculation
 * @date 21.5.2026
 */
#pragma once
#include "ManagerBase.hpp"
#include "raylib.h"
#include "rlights.h"
#include "world/WorldObjectBase.hpp"

namespace game
{
namespace world
{
class World;
}

namespace camera
{
// TODO: remove most of it, make fixed angle and distance
// follow invisible CameraAnchor => to constructor
class GameCamera : public Manager
{
  private:
    Camera3D m_camera;
    // TODO: put it in config
    const Vector3 m_offset = {0.0f, 25.0f, 12.0f};
    float m_fovy = 50.0f;
    float m_camSpeed = 5.0f;

    game::world::WorldObject& m_cameraAnchor;

    Light m_lightWorld;
    Shader m_lightingShader;

  public:
    GameCamera(game::world::WorldObject& cameraAnchor);
    const Camera3D& GetCam() const { return m_camera; }
    void Update(float deltaTime);
    void Init() override;

    // apply effect method here
    // void Shake(intensity)
    // void Zoom(enum? just 3 zoom levels)???
};
} // namespace camera
} // namespace game
