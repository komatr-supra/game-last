/**
 * @file Logistic.hpp
 * @author your name (you@domain.com)
 * @brief everything about movement, loading cargo, delivery, etc...
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include "raylib.h"

#include <string>
#include <vector>

struct Road;

struct City
{
    int id;
    std::string Name;
    std::string Shortcut;
    Vector2 Position;
    std::vector<Road*> Connections;
};

struct Road
{
    City* cityA;
    City* cityB;
    float lenght;
};
