#include "Renderer.hpp"

Renderer::Renderer(World &world) : m_world(world) {

    font = LoadFont("assets/dekatron.semibold.otf");
    mapTexture = LoadTexture("assets/map.png");
    circleTexture = LoadTexture("assets/circle.png");
}

Renderer::~Renderer() { UnloadTexture(circleTexture); }
void Renderer::DrawCities() {

    Node *selectedCity = nullptr;
    if (std::holds_alternative<Node *>(m_world.selected)) {
        selectedCity = std::get<Node *>(m_world.selected);
    }

    for (auto &city : m_world.Cities) {
        DrawTexture(circleTexture, city->Position.x - circleTexture.width / 2,
                    city->Position.y - circleTexture.height / 2,
                    city.get() == selectedCity ? WHITE : LIGHTGRAY);
    }
}
void Renderer::DrawRoads() {
    Road *selectedRoad = nullptr;
    if (std::holds_alternative<Road *>(m_world.selected)) {
        selectedRoad = std::get<Road *>(m_world.selected);
    }
    for (auto &road : m_world.Roads) {
        DrawLineEx(road->cityA->Position, road->cityB->Position, 5,
                   road.get() == selectedRoad ? WHITE : LIGHTGRAY);
    }
}

void Renderer::Draw() {
    DrawRoads();
    DrawCities();
}
