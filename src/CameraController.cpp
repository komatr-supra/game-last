#include "CameraController.hpp"

void CameraController::ClampToMap() {
    Vector2 halfScreen = {GetScreenWidth() / (2.0f * cam.zoom),
                          GetScreenHeight() / (2.0f * cam.zoom)};

    cam.target.x = Clamp(cam.target.x, halfScreen.x, m_worldSize.x - halfScreen.x);
    cam.target.y = Clamp(cam.target.y, halfScreen.y, m_worldSize.y - halfScreen.y);
}

CameraController::CameraController(int screenWidth, int screenHeight, Vector2 worldSize) {
    m_worldSize = worldSize;
    cam.target = {1020, 900};
    cam.offset = {static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2};
    cam.rotation = 0.0f;
    cam.zoom = 0.8f;
    ClampToMap();
}

CameraController::~CameraController() {}
void CameraController::MoveCamera(Vector2 target, bool instantMove) {
    if (instantMove) {
        cam.target = target;
    } else {
        cam.target = Vector2Add(cam.target, target);
    }
    ClampToMap();
}