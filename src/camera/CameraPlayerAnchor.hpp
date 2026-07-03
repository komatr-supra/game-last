#pragma once
#include "world/World.hpp"
#include "world/WorldObjectBase.hpp"
namespace game::core
{

class CameraPlayerAnchor : public game::world::WorldObject
{
    CameraPlayerAnchor(Vector3 position, int uniqueID) : game::world::WorldObject(position, uniqueID, world::ObjectType::System) {};
};
} // namespace game::core
