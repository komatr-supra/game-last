#include "core/Camera.hpp"
namespace game::camera
{

void CameraController::ClampToMap()
{
    Vector2 halfScreen = {GetScreenWidth() / (2.0f), GetScreenHeight() / (2.0f)};

    m_cam.target.x = Clamp(m_cam.target.x, halfScreen.x, m_worldSize.x - halfScreen.x);
    m_cam.target.y = Clamp(m_cam.target.y, halfScreen.y, m_worldSize.y - halfScreen.y);
}

CameraController::CameraController(int screenWidth, int screenHeight)
{
    m_cam.target = {1020, 900};
    m_cam.offset = {static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2};
    m_cam.rotation = 0.0f;
    m_cam.zoom = 0.8f;
    ClampToMap();
}

CameraController::~CameraController() {}
void CameraController::MoveCamera(Vector2 target, bool instantMove)
{
    if (instantMove)
    {
        m_cam.target = target;
    }
    else
    {
        m_cam.target = Vector2Add(m_cam.target, target);
    }
    ClampToMap();
}
} // namespace game::camera