#include "World.hpp"

#include "Config.hpp"

#include "Logistic.hpp"
#include "core/AssetManager.hpp"

#include "json.hpp"
#include "raylib.h"
#include "raymath.h"

#include <fstream>
namespace game::world
{

World::World(game::core::AssetManager& assetManager)
    : m_am(assetManager), m_mapModel(assetManager.GetModel("map")), m_cityModel(assetManager.GetModel("building"))
{
}
World::~World() = default;
void World::Init()
{

    std::ifstream f(game::constant::path::WorldData);
    nlohmann::json data = nlohmann::json::parse(f);
    for (auto& city : data["cities"])
    {
        auto newNode = std::make_unique<City>();
        newNode->id = city["id"].get<int>();
        newNode->Name = city["name"].get<std::string>();
        newNode->Shortcut = city["code"].get<std::string>();
        newNode->Position = GetCityWorldPosition(city["x"].get<float>(), city["y"].get<float>());
        TraceLog(LOG_WARNING,
                 "City data created. Name: %s   Position: %.2f, %.2f, %.2f",
                 newNode->Name.c_str(),
                 newNode->Position.x,
                 newNode->Position.y,
                 newNode->Position.z);
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
        newRoad->lenght = Vector3Distance(cityA->Position, cityB->Position);

        cityA->Connections.push_back(newRoad.get());
        cityB->Connections.push_back(newRoad.get());

        m_roads.emplace_back(std::move(newRoad));
    }
}

Vector3 World::GetCityWorldPosition(float x, float y)
{
    // city position on the texture in normalized values
    float widthNormalized = x / static_cast<float>(m_am.GetTexture("map").width);
    float heightNormalized = y / static_cast<float>(m_am.GetTexture("map").height);
    TraceLog(LOG_WARNING, "city pos 2D x: %f, y: %f   .. normalized values  x:%.2f, y:%.2f", widthNormalized, heightNormalized);
    // real units X and Z coordination
    // texture is from top left corner, but plane have got center at {0, 0, 0}
    float worldX = widthNormalized * game::constant::settings::mapSizeX - game::constant::settings::mapSizeX / 2;
    float worldZ = heightNormalized * game::constant::settings::mapSizeY - game::constant::settings::mapSizeY / 2;
    return Vector3{worldX, 0, worldZ};
}
City* World::GetCityByID(int id)
{
    for (const auto& n : m_cities)
    {
        if (n->id == id) return n.get();
    }
    return nullptr;
}

Road* World::GetRoadBetweenCities(City* city1, City* city2)
{
    for (auto& road : m_roads)
    {
        if ((road->cityA == city1 || road->cityB == city1) && (road->cityA == city2 || road->cityB == city2)) return road.get();
    }
    return nullptr;
}

std::vector<Road*> World::GetRoadsFromCity(City* city)
{
    std::vector<Road*> roads;
    for (auto& road : m_roads)
    {
        if (road->cityA == city || road->cityB == city) roads.push_back(road.get());
    }
    return roads;
}
void World::Update(float DelatTime) {}

bool World::TryGetRaycast(Camera3D camera, Vector3& outputPoint)
{
    Vector2 mousePos = GetMousePosition();
    Ray mouseRay = GetMouseRay(mousePos, camera);
    RayCollision collision = GetRayCollisionMesh(mouseRay, m_mapModel.meshes[0], m_mapModel.transform);
    if (collision.hit)
    {
        outputPoint = collision.point;
        return true;
    }
    return false;
}

void World::Draw()
{
    // DrawCube({0, 0, 0}, 1, 1, 1, BLACK);
    DrawModel(m_mapModel, {0, 0, 0}, 1, WHITE);
    /*
    DrawSprite(m_mapSprite, {0, 0});
    for (auto& road : m_roads)
    {
        DrawLineEx(road->cityA->Position, road->cityB->Position, 5, GRAY);
    }
*/
    for (auto& city : m_cities)
    {
        // DrawSprite(m_citySprite, city->Position);
        //  DrawTextEx(m_font, city->Name.c_str(), {city->Position.x - 48, city->Position.y - 48}, 42, 10, GOLD);
        DrawModel(m_cityModel, city->Position, 1, WHITE);
    }
}

} // namespace game::world