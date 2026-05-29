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

#include "raylib.h"

namespace game::camera
{

#include "raylib.h"
#include <math.h>

class GameCamera
{
  private:
    Camera3D camera;
    float yaw = 0.0f;     // Úhel kolem dokola (v radiánech nebo stupních)
    float pitch = 0.4f;   // Úhel nad obzorem
    float radius = 10.0f; // Vzdálenost kamery od auta/bodu

  public:
    GameCamera()
    {
        camera.position = Vector3{0.0f, 0.0f, 0.0f};
        camera.target = Vector3{0.0f, 0.0f, 0.0f}; // Tady začíná náš neviditelný bod
        camera.up = Vector3{0.0f, 1.0f, 0.0f};     // Y je nahoru
        camera.fovy = 60.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    }

    void Update(Vector3 targetPosition, float dt)
    {
        // 1. Neviditelný bod (target) se přichytí na pozici auta
        camera.target = targetPosition;

        // 2. Ovládání myší (když držíš třeba pravé tlačítko)
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mouseDelta = GetMouseDelta();
            yaw += mouseDelta.x * 0.005f; // Citlivost otáčení
            pitch += mouseDelta.y * 0.005f;

            // Zámek pro pitch, aby kamera neudělala loping
            if (pitch > 1.5f)
                pitch = 1.5f; // cca 85 stupňů nahoru
            if (pitch < 0.1f)
                pitch = 0.1f; // nenecháme kameru zalézt pod zem
        }

        // 3. Zoomování pomocí kolečka myši
        radius -= GetMouseWheelMove() * 0.5f;
        if (radius < 2.0f)
            radius = 2.0f;
        if (radius > 30.0f)
            radius = 30.0f;

        // 4. MATEMATIKA: Přepočet Yaw/Pitch/Radius na X, Y, Z pozici kamery
        camera.position.x = camera.target.x + radius * cosf(pitch) * sinf(yaw);
        camera.position.y = camera.target.y + radius * sinf(pitch);
        camera.position.z = camera.target.z + radius * cosf(pitch) * cosf(yaw);
    }

    // Getter pro Raylib vykreslování
    Camera3D GetRaylibCamera() const { return camera; }
};

} // namespace game::camera
