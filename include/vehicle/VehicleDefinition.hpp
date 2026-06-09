#pragma once

#include <cstddef>
#include <string>

struct Model;
struct Sprite;

namespace game::vehicles
{

enum class CarType
{
    NOT_SET,
    Pickup,
    Van,
    Truck,
    LAST
};

struct VehicleDefinition
{
    std::string name;
    CarType type;
    int speedMax;
    int capacityMax;
    int price;
    const Sprite* sprite;
    size_t gameModelID;

    VehicleDefinition(std::string carName,
                      CarType typeOfTheCar,
                      int maximumSpeed,
                      int maximumCapacity,
                      int costInShop,
                      const Sprite& spriteInGui,
                      size_t modelID)
        : name(carName),
          type(typeOfTheCar),
          speedMax(maximumSpeed),
          capacityMax(maximumCapacity),
          price(costInShop),
          sprite(&spriteInGui),
          gameModelID(modelID)
    {
    }
};
} // namespace game::vehicles