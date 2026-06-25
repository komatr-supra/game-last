/**
 * @file Camera.hpp
 * @author your name (you@domain.com)
 * @brief setup and move camera, effects, zoom, etc...
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include "Core.hpp"
#include "raylib.h"
#include "rlights.h"
#include "tween.h"
namespace game::graphics
{

class GameCamera : public game::core::Manager
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

  public:
    GameCamera();
    const Camera3D& GetCam() const { return m_camera; }
    void Follow(const Vector3* target);
    void Unfollow();
    void Move(Vector2 direction);
    void Update(float deltaTime);
    void Init() override;
};

} // namespace game::graphics
