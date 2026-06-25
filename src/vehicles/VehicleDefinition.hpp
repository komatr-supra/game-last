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
    int id;
    std::string name;
    CarType type;
    int speedMax;
    int capacityMax;
    int price;
    const Sprite* sprite;
    size_t modelHandle;

    VehicleDefinition(int uniqueID,
                      std::string carName,
                      CarType typeOfTheCar,
                      int maximumSpeed,
                      int maximumCapacity,
                      int costInShop,
                      const Sprite& spriteInGui,
                      size_t handleID)
        : id(uniqueID),
          name(carName),
          type(typeOfTheCar),
          speedMax(maximumSpeed),
          capacityMax(maximumCapacity),
          price(costInShop),
          sprite(&spriteInGui),
          modelHandle(handleID)
    {
    }
};
} // namespace game::vehicles