#pragma once
#include "IPositionProvider.hpp"
#include "raylib.h"

namespace game::camera
{
class CameraPlayerAnchor : public IPositionProvider
{
  private:
    Vector3 m_position;

  public:
    CameraPlayerAnchor(Vector3 position) : m_position(position) {};
    const Vector3& GetPosition() const override { return m_position; }
};
} // namespace game::camera
