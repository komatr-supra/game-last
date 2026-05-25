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
#include "Sprite.hpp"
#include "raylib.h"

#include <memory>
#include <vector>

struct City;
struct Road;
class AssetManager;

class Map
{
  private:
    Sprite m_mapSprite;
    Sprite m_citySprite;
    Font m_font;
    std::vector<std::unique_ptr<City>> m_cities;
    std::vector<std::unique_ptr<Road>> m_roads;

  public:
    Map(AssetManager& assetManager);
    ~Map();

    City* GetCityByID(int id);
    Vector2 GetMapSize();
    Road* GetRoadBetweenCities(City* city1, City* city2);
    std::vector<Road*> GetRoadsFromCity(City* city);
    void Draw();
};
