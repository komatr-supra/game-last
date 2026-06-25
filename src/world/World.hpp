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

#include "Core.hpp"
#include "raylib.h"

#include <memory>
#include <vector>

#pragma region Forward declaration
namespace game::grahics
{
struct Sprite;
}

namespace game::core
{
class AssetManager;
}

namespace game::world
{
struct City;
struct Road;
} // namespace game::world
#pragma endregion

namespace game::world
{
class World : public game::core::Manager
{
  private:
    const game::core::AssetManager& m_am;
    const Model& m_mapModel;
    const Model& m_cityModel;
    Font m_font;
    std::vector<std::unique_ptr<City>> m_cities;
    std::vector<std::unique_ptr<Road>> m_roads;

    Vector3 GetCityWorldPosition(float x, float y);

  public:
    World(game::core::AssetManager& assetManager);
    ~World();
    void Init() override;
    City* GetCityByID(int id);
    Road* GetRoadBetweenCities(City* city1, City* city2);
    std::vector<Road*> GetRoadsFromCity(City* city);
    bool TryGetRaycast(Camera3D camera, Vector3& outputPoint);
    void Update(float deltaTime);
    void Draw();
};
} // namespace game::world