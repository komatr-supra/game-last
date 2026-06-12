#pragma once

#include "raylib.h"

class WorldObject
{
  protected:
    Vector2 m_position;

  public:
    virtual ~WorldObject() = default;
    Vector2 GetPosition() const { return m_position; }
};