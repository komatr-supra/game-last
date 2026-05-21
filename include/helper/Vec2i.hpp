#pragma once

#include "raylib.h"

#include <cmath>

struct Vector2i {
    int x;
    int y;

    Vector2i(const Vector2 &v) {
        x = static_cast<int>(std::round(v.x));
        y = static_cast<int>(std::round(v.y));
    }
};
