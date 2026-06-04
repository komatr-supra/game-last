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

#include "WorldObject.hpp"
#include "raylib.h"

#include <math.h>

namespace game::camera
{
class CameraAnchor : public game::world::WorldObject
{
  public:
    const game::world::WorldObject* targetObject = nullptr;

    void SetTarget(const game::world::WorldObject* target)
    {
        if (target)
            targetObject = target;
    }
    Vector3 GetPosition() const { return targetObject ? targetObject->GetPosition() : position; }
};

class GameCamera
{
  private:
    Camera3D camera;
    float yaw = 0.0f;     // Úhel kolem dokola (v radiánech nebo stupních)
    float pitch = 0.9f;   // Úhel nad obzorem
    float radius = 30.0f; // Vzdálenost kamery od auta/bodu
    float fovy = 30.0f;

    void CalculatePosition();

  public:
    CameraAnchor cameraAnchor;
    GameCamera();
    Camera3D GetCam() const { return camera; }
    void SetTarget(const game::world::WorldObject* target);

    void Update(float deltaTime);
};

} // namespace game::camera
