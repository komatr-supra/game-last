#include "Camera.hpp"

#include "raylib.h"
#include "raymath.h"
#include "tweeny.h"
#include <array>

namespace game::camera
{
GameCamera::GameCamera() : m_trackedPosition(nullptr), m_desiredPosition{0, 0, 0}, m_moveDir{0, 0}
{
    m_camera.position = Vector3{0.0f, 0.0f, 0.0f};
    m_camera.target = Vector3{0.0f, 0.0f, 0.0f};
    m_camera.up = Vector3{0.0f, 1.0f, 0.0f};
    m_camera.projection = CAMERA_PERSPECTIVE;
    CalculatePosition();
}

void GameCamera::CalculatePosition()
{
    m_camera.fovy = m_fovy;
    m_camera.position.x = m_camera.target.x + m_radius * cosf(m_pitch) * sinf(m_yaw);
    m_camera.position.y = m_camera.target.y + m_radius * sinf(m_pitch);
    m_camera.position.z = m_camera.target.z + m_radius * cosf(m_pitch) * cosf(m_yaw);
}

void GameCamera::Follow(const Vector3* target)
{
    if (target)
    {
        auto tween = tweeny::from(0).to(100).during(100).via(tweeny::easing::linear);
        // m_trackedPosition = target;
        HideCursor();
        SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
        /*
                m_moveTween = tweeny::from(m_camera.target.x, m_camera.target.z)
                                  .to(target->x, target->z)
                                  .during(400)
                                  .via(tweeny::easing::cubicInOut);*/
    }
}

void GameCamera::Unfollow()
{
    m_desiredPosition = m_camera.target;
    m_trackedPosition = nullptr;
}

void GameCamera::Move(Vector2 direction)
{
    Unfollow();
    m_moveDir = direction;
}

void GameCamera::Update(float deltaTime)
{
    if (m_trackedPosition)
    {
        m_desiredPosition = *m_trackedPosition;
    }
    else if (m_moveDir != Vector2Zero())
    {
        m_desiredPosition.x += m_moveDir.x * m_camSpeed * deltaTime;
        m_desiredPosition.z += m_moveDir.y * m_camSpeed * deltaTime;
    }

    if (m_moveTween.progress() < 1.0f)
    {
        auto current = m_moveTween.step(static_cast<int>(deltaTime * 1000));
        m_camera.target.x = current[0];
        m_camera.target.z = current[1];
    }
    else
    {
        ShowCursor();
    }
    // m_camera.target = Vector3Lerp(m_camera.target, m_desiredPosition, deltaTime * 0.005f);
    CalculatePosition();
}

} // namespace game::camera