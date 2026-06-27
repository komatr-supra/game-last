/**
 * @file Logistic.hpp
 * @author komatr
 * @brief cities and paths system = everything about movement, pathfinding etc...
 * @date 21.5.2026
 */
// TODO: make it a complete system
#pragma once
#include "raylib.h"

#include <string>
#include <vector>

namespace game::world
{
struct Road;
struct City
{
    int id;
    std::string Name;
    std::string Shortcut;
    Vector3 Position;
    std::vector<Road*> Connections;
};
struct Road
{
    City* cityA;
    City* cityB;
    float lenght;
};
} // namespace game::world