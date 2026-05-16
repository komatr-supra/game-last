#include "World.hpp"
World::World(/* args */) {
    std::ifstream f("data.json");
    nlohmann::json data = nlohmann::json::parse(f);
    for (auto &city : data["cities"]) {
        auto newNode = std::make_unique<Node>();
        newNode->id = city["id"].get<int>();
        newNode->Name = city["name"].get<std::string>();
        newNode->Shortcut = city["code"].get<std::string>();
        newNode->Position = {city["x"].get<float>(), city["y"].get<float>()};
        Cities.push_back(std::move(newNode));
    }
    for (auto &path : data["roads"]) {
        // get cityA
        Node *cityA = FindCityByID(path["a"]);
        Node *cityB = FindCityByID(path["b"]);
        auto newRoad = std::make_unique<Road>();
        newRoad->cityA = cityA;
        newRoad->cityB = cityB;
        newRoad->lenght = Vector2Distance(cityA->Position, cityB->Position);

        cityA->Connections.push_back(newRoad.get());
        cityB->Connections.push_back(newRoad.get());

        Roads.emplace_back(std::move(newRoad));
    }
}

World::~World() {}

Node *World::FindCityByID(int id) {
    for (const auto &n : Cities) {
        if (n->id == id)
            return n.get();
    }
    return nullptr;
}

bool World::Hover(Vector2 worldPos) {
    for (auto &city : Cities) {
        float distance = Vector2Distance(worldPos, city->Position);
        if (distance < 64) {
            hovered = city.get();
            return true;
        }
    }
    for (auto &road : Roads) {
        if (CheckCollisionPointLine(worldPos, road->cityA->Position, road->cityB->Position,
                                    15.0f)) {
            hovered = road.get();
            return true;
        }
    }
    hovered = std::monostate{};
    return false;
}

WorldObject World::Select() {

    if (std::holds_alternative<std::monostate>(hovered)) {
        selected = std::monostate{};
    } else {
        selected = hovered;
    }
    return selected;
}

Road *World::GetRoadBetweenCities(Node *city1, Node *city2) {
    for (auto &road : Roads) {
        if ((road->cityA == city1 || road->cityB == city1) &&
            (road->cityA == city2 || road->cityB == city2))
            return road.get();
    }
    return nullptr;
}

std::vector<Road *> World::GetRoadsFromCity(Node *city) {
    std::vector<Road *> roads;
    for (auto &road : Roads) {
        if (road->cityA == city || road->cityB == city)
            roads.push_back(road.get());
    }
}
