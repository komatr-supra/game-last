/**
 * @file Vec2i.hpp
 * @author your name (you@domain.com)
 * @brief Vector 2 Integer version
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include "raylib.h"

#include <cmath>

struct Vector2i
{
    int x;
    int y;

    Vector2i(const Vector2& v)
    {
        x = static_cast<int>(std::round(v.x));
        y = static_cast<int>(std::round(v.y));
    }
};
