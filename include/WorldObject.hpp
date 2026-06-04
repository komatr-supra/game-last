#pragma once

#include "raylib.h"

namespace game::world
{
class WorldObject
{
  protected:
    Vector3 position;

  public:
    ~WorldObject() = default;
    Vector3 GetPosition() const { return position; }
};
} // namespace game::world