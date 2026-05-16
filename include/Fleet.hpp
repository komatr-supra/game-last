#pragma once
#include "Node.hpp"
#include "raylib.h"
#include "raymath.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <vector>

struct Vector2i {
    int x;
    int y;

    Vector2i(const Vector2 &v) {
        x = static_cast<int>(std::round(v.x));
        y = static_cast<int>(std::round(v.y));
    }
};

class GameTime {
  private:
    struct Callback {
        int id;
        std::function<void(unsigned int)> callback;
    };
    unsigned int m_totalTicks;
    float m_timeMultiplier = 1.0f;
    float m_timeRealAccumulated = 0.0f;
    std::unordered_map<int, std::function<void(unsigned int)>> m_callbacks;
    int subscriberHandle = 0;
    const float REAL_SECONDS_PER_TICK = 1.0f;
    const unsigned int TICKS_PER_HOUR = 60;
    const unsigned int TICKS_PER_DAY = 24 * TICKS_PER_HOUR;
    void TriggerSubscribers() {
        for (const auto &[id, callback] : m_callbacks) {
            callback(m_totalTicks);
        }
    }

  public:
    void Update(float deltaTime) {
        if (m_timeMultiplier <= 0.0f)
            return;

        m_timeRealAccumulated += deltaTime * m_timeMultiplier;

        while (m_timeRealAccumulated >= REAL_SECONDS_PER_TICK) {
            m_totalTicks++;
            m_timeRealAccumulated -= REAL_SECONDS_PER_TICK;
        }
    }

    int SubscribeCallback(std::function<void(unsigned int)> callback) {
        int id = subscriberHandle++;
        m_callbacks[id] = callback;
        return id;
    }
    void UnsubscribeCallback(int handle) { m_callbacks.erase(handle); }
    // Pomocné metody pro získání lidsky čitelného času
    unsigned int getHour() const { return (m_totalTicks / TICKS_PER_HOUR) % 24; }
    unsigned int getDay() const { return (m_totalTicks / TICKS_PER_DAY) + 1; }
    unsigned int getMinute() const { return m_totalTicks % TICKS_PER_HOUR; }
};
// coplete data for order
struct Order {
    Node *from;
    Node *to;
    int size;
    int reward;
    int penality;
};
// single unit of order
struct OrderUnit {
    Order *order;
    int amount;
};
struct PathData {
    Node *city;
    Road *road;
};
// car data
class Car {
  public:
    std::string name;
    std::string type;
    int speed;
    Node *city = nullptr;
    float progress = 0.0f;
    int capacity;
    std::vector<OrderUnit *> cargo;
    std::vector<PathData> Path;

    Vector2 GetPosition() {
        // no path, car is in city
        if (Path.empty()) {
            return city->Position;
        }
        // get position on road, "city" is where car going
        Node *endCity =
            Path[0].city == Path[0].road->cityB ? Path[0].road->cityB : Path[0].road->cityA;
        return Vector2Lerp(city->Position, endCity->Position, progress);
    }
    void Update(float time) {
        if (Path.empty())
            return;
        // move on the road by carspeed, normalize distance
        progress += speed / Path[0].road->lenght * time;
        if (progress >= 1.0f) {
            city = Path[0].city;
            // next target
            Path.erase(Path.begin());
            progress = 0.0f;
        }
    }
    void AddPointToPath(Node *targetCity, Road *usedRoad) {
        PathData newPathData;
        newPathData.city = targetCity;
        newPathData.road = usedRoad;
        Path.emplace_back(newPathData);
        TraceLog(LOG_ERROR, "pridano mesto %s do jizdniho radu", targetCity->Name.c_str());
    }
};
class Fleet {
  private:
    std::vector<std::unique_ptr<Car>> Cars;

  public:
    Fleet(/* args */);
    ~Fleet();
    // make a car factory pattern
    Car *CreateCar(Node *startingCity) {
        auto newCar = std::make_unique<Car>();
        newCar->name = "auto";
        newCar->type = "nakladak";
        newCar->capacity = 6;
        newCar->speed = 80;
        newCar->city = startingCity;

        auto car = newCar.get();
        Cars.emplace_back(std::move(newCar));
        return car;
    }

    void Update(float time) {
        for (auto &car : Cars) {
            car->Update(time);
        }
    }

    void Draw() {
        for (auto &car : Cars) {
            Vector2i position = car->GetPosition();
            DrawCircle(position.x, position.y, 15, RED);
        }
    }
};

Fleet::Fleet(/* args */) {}

Fleet::~Fleet() {}
