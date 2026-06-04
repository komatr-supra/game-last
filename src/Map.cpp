#include "Config.hpp"

#include "AssetManager.hpp"
#include "Logistic.hpp"
#include "Map.hpp"
#include "json.hpp"
#include "raylib.h"
#include "raymath.h"

#include <fstream>
namespace game::world
{

Map::Map(game::assets::AssetManager& assetManager)
    : m_mapModel(assetManager.GetModel("map")), m_cityModel(assetManager.GetModel("assets/models/building-h"))
{

    std::ifstream f(game::constant::path::WorldData);
    nlohmann::json data = nlohmann::json::parse(f);
    for (auto& city : data["cities"])
    {
        auto newNode = std::make_unique<City>();
        newNode->id = city["id"].get<int>();
        newNode->Name = city["name"].get<std::string>();
        newNode->Shortcut = city["code"].get<std::string>();
        newNode->Position = {city["x"].get<float>(), city["y"].get<float>()};
        m_cities.push_back(std::move(newNode));
    }
    for (auto& roadData : data["roads"])
    {
        // get cityA
        City* cityA = GetCityByID(roadData["a"]);
        City* cityB = GetCityByID(roadData["b"]);
        auto newRoad = std::make_unique<Road>();
        newRoad->cityA = cityA;
        newRoad->cityB = cityB;
        newRoad->lenght = Vector2Distance(cityA->Position, cityB->Position);

        cityA->Connections.push_back(newRoad.get());
        cityB->Connections.push_back(newRoad.get());

        m_roads.emplace_back(std::move(newRoad));
    }
}

Map::~Map() {}

City* Map::GetCityByID(int id)
{
    for (const auto& n : m_cities)
    {
        if (n->id == id)
            return n.get();
    }
    return nullptr;
}

Road* Map::GetRoadBetweenCities(City* city1, City* city2)
{
    for (auto& road : m_roads)
    {
        if ((road->cityA == city1 || road->cityB == city1) && (road->cityA == city2 || road->cityB == city2))
            return road.get();
    }
    return nullptr;
}

std::vector<Road*> Map::GetRoadsFromCity(City* city)
{
    std::vector<Road*> roads;
    for (auto& road : m_roads)
    {
        if (road->cityA == city || road->cityB == city)
            roads.push_back(road.get());
    }
    return roads;
}
void Map::Draw()
{
    // DrawCube({0, 0, 0}, 1, 1, 1, BLACK);
    DrawModel(m_mapModel, {-5, 0, -5}, 1, WHITE);
    /*
    DrawSprite(m_mapSprite, {0, 0});
    for (auto& road : m_roads)
    {
        DrawLineEx(road->cityA->Position, road->cityB->Position, 5, GRAY);
    }

    for (auto& city : m_cities)
    {
        DrawSprite(m_citySprite, city->Position);
        // DrawTextEx(m_font, city->Name.c_str(), {city->Position.x - 48, city->Position.y - 48}, 42, 10, GOLD);
    }
        */
}

} // namespace game::world