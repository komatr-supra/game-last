/**
 * @file Logistic.hpp
 * @author komatr
 * @brief everything about movement
 * @date 21.5.2026
 */
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