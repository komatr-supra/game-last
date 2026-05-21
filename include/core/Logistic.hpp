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

struct PathData
{
    City* city; // destination city
    Road* road;
};
