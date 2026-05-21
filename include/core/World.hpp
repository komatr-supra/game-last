#pragma once

#include "Sprite.hpp"

#include "raylib.h"

#include <memory>
#include <vector>

struct City;
struct Road;
class AssetManager;

class World
{
  private:
    City* FindCityByID(int id);
    Sprite m_mapSprite;
    Sprite m_citySprite;
    Font m_font;
    std::vector<std::unique_ptr<City>> m_cities;
    std::vector<std::unique_ptr<Road>> m_roads;

  public:
    World(AssetManager& assetManager);
    ~World();

    Vector2 GetMapSize();
    Road* GetRoadBetweenCities(City* city1, City* city2);
    std::vector<Road*> GetRoadsFromCity(City* city);
    void Draw();
    void LoadSprites();
};
