#pragma once

#include "raylib.h"

class WorldObject
{
  protected:
    Vector3 m_position;

  public:
    virtual ~WorldObject() = default;
    Vector3 GetPosition() const { return m_position; }
};