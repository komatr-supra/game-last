#pragma once
#include <string>
#include <vector>
#include "raylib.h"
struct Road;
struct Node
    {
        int id;
        std::string Name;
        std::string Shortcut;
        Vector2 Position;
        std::vector<Road*> Connections;
    };

struct Road{
    Node* cityA;
    Node* cityB;
    float lenght;
};