#pragma once

#include "raylib.h"

struct Padding
{
    float right;
    float top;
    float left;
    float bot;
};

struct MouseContext
{
    Vector2 position = {0, 0};
    bool leftPressed = false;
};
