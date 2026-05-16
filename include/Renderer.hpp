#pragma once
#include "World.hpp"
#include "raylib.h"
class Renderer {
  private:
    Font font;
    Texture2D mapTexture;
    Texture2D circleTexture;
    World &m_world;
    void DrawCities();
    void DrawRoads();

  public:
    void Draw();
    Renderer(World &world);
    ~Renderer();
};