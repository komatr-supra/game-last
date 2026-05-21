#include "Config.hpp"

#include "core/AssetManager.hpp"
#include "core/Logistic.hpp"
#include "core/World.hpp"

#include "json.hpp"
#include "raymath.h"

#include <fstream>

World::World(AssetManager& assetManager)
{
    m_mapSprite = assetManager.GetSprite("map");
    m_citySprite = assetManager.GetSprite("city");
    m_font = LoadFont(Config::FilePaths::Font);

    std::ifstream f(Config::FilePaths::MapData);
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
        City* cityA = FindCityByID(roadData["a"]);
        City* cityB = FindCityByID(roadData["b"]);
        auto newRoad = std::make_unique<Road>();
        newRoad->cityA = cityA;
        newRoad->cityB = cityB;
        newRoad->lenght = Vector2Distance(cityA->Position, cityB->Position);

        cityA->Connections.push_back(newRoad.get());
        cityB->Connections.push_back(newRoad.get());

        m_roads.emplace_back(std::move(newRoad));
    }
}

World::~World() {}

City* World::FindCityByID(int id)
{
    for (const auto& n : m_cities)
    {
        if (n->id == id)
            return n.get();
    }
    return nullptr;
}

Road* World::GetRoadBetweenCities(City* city1, City* city2)
{
    for (auto& road : m_roads)
    {
        if ((road->cityA == city1 || road->cityB == city1) && (road->cityA == city2 || road->cityB == city2))
            return road.get();
    }
    return nullptr;
}

std::vector<Road*> World::GetRoadsFromCity(City* city)
{
    std::vector<Road*> roads;
    for (auto& road : m_roads)
    {
        if (road->cityA == city || road->cityB == city)
            roads.push_back(road.get());
    }
    return roads;
}
void World::Draw()
{
    DrawSprite(m_mapSprite, {0, 0});
    for (auto& road : m_roads)
    {
        DrawLineEx(road->cityA->Position, road->cityB->Position, 5, GRAY);
    }
    for (auto& city : m_cities)
    {
        DrawSprite(m_citySprite, city->Position);
        DrawTextEx(m_font, city->Name.c_str(), {city->Position.x - 48, city->Position.y - 48}, 42, 10, GOLD);
    }
}

Vector2 World::GetMapSize()
{
    return {static_cast<float>(m_mapSprite.sourceRect.width), static_cast<float>(m_mapSprite.sourceRect.height)};
}

void World::LoadSprites() {}
