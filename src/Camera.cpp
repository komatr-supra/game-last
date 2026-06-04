#include "Camera.hpp"

#include "raylib.h"
#include "raymath.h"

namespace game::camera
{
GameCamera::GameCamera()
{
    camera.position = Vector3{0.0f, 0.0f, 0.0f};
    camera.target = Vector3{0.0f, 0.0f, 0.0f}; // Tady začíná náš neviditelný bod
    camera.up = Vector3{0.0f, 1.0f, 0.0f};     // Y je nahoru

    camera.projection = CAMERA_PERSPECTIVE;
    CalculatePosition();
}

void GameCamera::CalculatePosition()
{
    camera.fovy = fovy;
    camera.position.x = camera.target.x + radius * cosf(pitch) * sinf(yaw);
    camera.position.y = camera.target.y + radius * sinf(pitch);
    camera.position.z = camera.target.z + radius * cosf(pitch) * cosf(yaw);
}

void GameCamera::SetTarget(const game::world::WorldObject* target)
{
    if (target)
        cameraAnchor.SetTarget(target);
}

void GameCamera::Update(float deltaTime)
{
    // if (cameraAnchor.targetObject == nullptr)
    //   return;
    // float cameraMoveSpeed = deltaTime * 10.0f;
    // camera.target = Vector3Lerp(camera.target, cameraAnchor.GetPosition(), cameraMoveSpeed);
}

} // namespace game::camera