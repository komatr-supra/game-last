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