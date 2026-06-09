#pragma once

#include "AssetManager.hpp"
#include "Map.hpp"
#include "WorldObject.hpp"

namespace game::world
{
class World
{
  private:
    Map& m_map;
    game::assets::AssetManager& m_am;
};
} // namespace game::world