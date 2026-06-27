/**
 * @file World.hpp
 * @author komatr
 * @brief take care about map, cities and paths... the world...
 * @date 21.5.2026
 */
#pragma once
#include "raylib.h"

#include "Id.hpp"
#include "Logistic.hpp"
#include "ManagerBase.hpp"
#include "WorldObjectBase.hpp"
#include <memory>
#include <vector>

namespace game
{
namespace core
{
class AssetManager;
}
namespace world
{
struct WorldObjectType
{
};

class World : public Manager
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
    WorldObject* GetWorldObject(TypeID<WorldObjectType> id) const;
    void Update(float deltaTime);
    void Draw();
};
} // namespace world
} // namespace game