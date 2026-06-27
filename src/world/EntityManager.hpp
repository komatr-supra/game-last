#pragma once
#include "Id.hpp"
#include "ManagerBase.hpp"

namespace game
{

namespace world
{
class WorldObject;
}

namespace core
{
// unique id for entities

class EntityManager : public Manager
{
  private:
  public:
    const world::WorldObject* GetInstanceByID() const;
};
} // namespace core
} // namespace game