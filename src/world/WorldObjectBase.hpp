// base world object in the game
#pragma once
#include "NonCopyable.hpp"
#include "raymath.h"
namespace game::world
{
enum class ObjectType
{
    Vehicle,
    City,
    Road,
    System
};
class WorldObject : public NonCopyable
{
  protected:
    Vector3 m_position;

  public:
    const int id;
    const ObjectType type;
    WorldObject(Vector3 position, int uniqueID, ObjectType objectType) : m_position(position), id(uniqueID), type(objectType) {};
    Vector3 GetPosition() const { return m_position; }
};
} // namespace game::world