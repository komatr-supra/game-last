#pragma once
#include "Node.hpp"
#include "json.hpp"
#include "raylib.h"
#include "raymath.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
class World {
  private:
    Node *FindCityByID(int id);

  public:
    std::vector<std::unique_ptr<Node>> Cities;
    std::vector<std::unique_ptr<Road>> Roads;

    Road *GetRoadBetweenCities(Node *city1, Node *city2);
    std::vector<Road *> GetRoadsFromCity(Node *city);
    World(/* args */);
    ~World();
};
