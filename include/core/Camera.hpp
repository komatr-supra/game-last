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
#include "raymath.h"

class CameraController
{
  private:
    Camera2D m_cam;
    Vector2 m_worldSize;

    void ClampToMap();

  public:
    CameraController(int screenWidth, int screenHeight, Vector2 worldSize);
    ~CameraController();

    Camera2D& GetCamera() { return m_cam; }
    void MoveCamera(Vector2 target, bool instantMove = false);
};
