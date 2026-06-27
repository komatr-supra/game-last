/**
 * @file Camera.hpp
 * @author komatr
 * @brief setup and move camera, effects, zoom, etc...
 * @date 21.5.2026
 */
#pragma once
#include "ManagerBase.hpp"
#include "raylib.h"
#include "rlights.h"
#include "tween.h"
#include "world/World.hpp"

namespace game::world
{
class World;
}

namespace game::core
{
class EntityManager;
}

namespace game::graphics
{

class GameCamera : public Manager
{
  private:
    Camera3D m_camera;
    float m_yaw = 0.0f;
    float m_pitch = 0.9f;
    float m_radius = 20.0f;
    float m_fovy = 50.0f;
    const Vector3* m_trackedPosition;
    Vector3 m_desiredPosition;
    float m_camSpeed = 5.0f;
    Vector2 m_moveDir;
    void CalculatePosition();
    Light m_lightWorld;
    Shader m_lightingShader;

    // tweeny test
    tweeny::tween<float, float> m_moveTween;

    game::world::World& m_world;

  public:
    GameCamera(game::world::World& world);
    const Camera3D& GetCam() const { return m_camera; }
    void FollowEntity(TypeID<game::world::WorldObjectType> entityID);
    void Unfollow();
    void Move(Vector2 direction);
    void Update(float deltaTime);
    void Init() override;
};

} // namespace game::graphics
