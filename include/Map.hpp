/**
 * @file Map.hpp
 * @author your name (you@domain.com)
 * @brief take care about map, cities and paths
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#include "raylib.h"

#include <memory>
#include <vector>

namespace game::world
{
struct City;
struct Road;
} // namespace game::world

namespace game::assets
{
struct Sprite;
class AssetManager;
} // namespace game::assets

namespace game::world
{

class Map
{
  private:
    const Model& m_mapModel;
    const Model& m_cityModel;
    Font m_font;
    std::vector<std::unique_ptr<City>> m_cities;
    std::vector<std::unique_ptr<Road>> m_roads;

  public:
    Map(game::assets::AssetManager& assetManager);
    ~Map();

    City* GetCityByID(int id);
    Road* GetRoadBetweenCities(City* city1, City* city2);
    std::vector<Road*> GetRoadsFromCity(City* city);
    void Draw();
};
} // namespace game::world