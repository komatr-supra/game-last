/**
 * @file VehicleDefinition.hpp
 * @author your name (you@domain.com)
 * @brief just information about vehicle. this struct is saved in vehicle database.
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <string>

struct VehicleDefinition
{
    std::string nameInternal;
    std::string nameType;
    int speedMax;
    int capacityMax;
    int price;
    std::string texturePath;

    VehicleDefinition(std::string internal, std::string type, int speed, int cap, int p, std::string tex)
        : nameInternal(std::move(internal)),
          nameType(std::move(type)),
          speedMax(speed),
          capacityMax(cap),
          price(p),
          texturePath(std::move(tex))
    {
    }
};